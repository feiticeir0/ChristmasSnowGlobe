    /*
 * Snow Simulation with Dynamic Backgrounds and Touch Input
 * 
 * Author: Bruno Santos <feiticeir0@whatgeek.com.pt>
 * 
 * This is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>

#define NUM_SNOWFLAKES 80 // Number of snowflakes in the simulation

// Struct representing a snowflake
typedef struct {
    int x, y;        // Position of the snowflake
    int size;        // Size of the snowflake
    float speed;     // Falling speed of the snowflake
} Snowflake;

// Wind effect variables
float wind_speed = 0.0f;           // Current wind speed
float wind_acceleration = 0.02f;  // How quickly wind changes

/**
 * Initializes a snowflake with a starting position and speed.
 * 
 * @param snowflake Pointer to the snowflake to initialize.
 * @param reset_position Determines where the snowflake should reset:
 *                       0: Random x position, above the screen.
 *                      -1: Entering from the left.
 *                       1: Entering from the right.
 * @param width Screen width.
 * @param height Screen height.
 */
void init_snowflake(Snowflake *snowflake, int reset_position, int width, int height) {
    if (reset_position == 0) {
        snowflake->x = rand() % width; // Random x position
    } else if (reset_position == -1) {
        snowflake->x = -10;           // Off-screen on the left
    } else if (reset_position == 1) {
        snowflake->x = width + 10;    // Off-screen on the right
    }
    snowflake->y = rand() % height - height; // Start above the screen
    snowflake->size = rand() % 3 + 4;        // Random size between 2 and 6
    snowflake->speed = (float)(rand() % 300 + 200) / 100.0f; // Speed between 2.0 and 5.0
}

/**
 * Updates the position of a snowflake.
 * Applies wind effects and resets position if the snowflake moves out of bounds.
 * 
 * @param snowflake Pointer to the snowflake to update.
 * @param width Screen width.
 * @param height Screen height.
 */
void update_snowflake(Snowflake *snowflake, int width, int height) {
    snowflake->x += (int)(wind_speed * (5.0f / snowflake->size)); // Wind effect
    snowflake->y += (int)snowflake->speed;                       // Falling speed

    // Reset snowflake if it moves out of bounds
    if (snowflake->y > height) {
        init_snowflake(snowflake, 0, width, height);
    } else if (snowflake->x < -10) {
        init_snowflake(snowflake, 1, width, height);
    } else if (snowflake->x > width + 10) {
        init_snowflake(snowflake, -1, width, height);
    }
}

/**
 * Dynamically adjusts wind speed over time.
 * Wind alternates between left, right, and calm conditions.
 */
void update_wind() {
    wind_speed += ((rand() % 3) - 1) * wind_acceleration; // Randomly adjust wind
    if (wind_speed > 2.0f) wind_speed = 2.0f;             // Cap maximum wind speed
    if (wind_speed < -2.0f) wind_speed = -2.0f;           // Cap minimum wind speed
}

/**
 * Loads all JPEG textures from a given directory.
 * 
 * @param renderer Pointer to the SDL renderer.
 * @param directory Path to the directory containing JPEG files.
 * @param textures Pointer to an array of SDL_Texture pointers.
 * @return Number of textures loaded.
 */
int load_textures(SDL_Renderer *renderer, const char *directory, SDL_Texture ***textures) {
    DIR *dir = opendir(directory);
    if (!dir) {
        printf("Failed to open directory: %s\n", directory);
        return 0;
    }

    struct dirent *entry;
    int count = 0;
    SDL_Texture **temp_textures = NULL;

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".jpg")) { // Check for JPEG files
            char filepath[512]; // Increased buffer size to handle longer paths
            int written = snprintf(filepath, sizeof(filepath), "%s/%s", directory, entry->d_name);

            if (written < 0 || written >= sizeof(filepath)) {
                printf("Error: File path truncated for %s/%s\n", directory, entry->d_name);
                continue;
            }

            SDL_Surface *surface = IMG_Load(filepath); // Load image
            if (!surface) {
                printf("Failed to load image: %s\n", filepath);
                continue;
            }

            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface); // Free surface after creating texture
            if (!texture) {
                printf("Failed to create texture: %s\n", filepath);
                continue;
            }

            temp_textures = realloc(temp_textures, (count + 1) * sizeof(SDL_Texture *));
            temp_textures[count++] = texture; // Add texture to the array
        }
    }

    closedir(dir); // Close the directory
    *textures = temp_textures;
    return count;
}


/**
 * Displays help information for command-line arguments.
 */
void display_help() {
    printf("Usage: snow_simulation -w WIDTH -h HEIGHT -e DEVICE\n");
    printf("Options:\n");
    printf("  -w WIDTH          Set the screen width\n");
    printf("  -h HEIGHT         Set the screen height\n");
    printf("  -e DEVICE         Set the touchscreen input device\n");
    printf("  --help            Show this help message and exit\n");
}

int main(int argc, char *argv[]) {
    // Default values
    int width = 0;
    int height = 0;
    const char *device_path = NULL;

    // Command-line argument parsing
    int opt;
    while ((opt = getopt(argc, argv, "w:h:e:")) != -1) {
        switch (opt) {
            case 'w':
                width = atoi(optarg);
                break;
            case 'h':
                height = atoi(optarg);
                break;
            case 'e':
                device_path = optarg;
                break;
            default:
                display_help();
                return 1;
        }
    }

    // Handle --help
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            display_help();
            return 0;
        }
    }

    // Ensure all required arguments are provided
    if (width == 0 || height == 0 || device_path == NULL) {
        display_help();
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0 || IMG_Init(IMG_INIT_PNG) == 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Snow Simulation with Dynamic Resolution",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          width, height, SDL_WINDOW_FULLSCREEN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    const char *image_directory = "./images";
    SDL_Texture **backgrounds;
    int num_backgrounds = load_textures(renderer, image_directory, &backgrounds);
    if (num_backgrounds == 0) {
        printf("No backgrounds loaded. Exiting.\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    struct libevdev *dev = NULL;
    int fd = open(device_path, O_RDONLY | O_NONBLOCK);
    if (fd < 0 || libevdev_new_from_fd(fd, &dev) < 0) {
        printf("Failed to initialize libevdev for touch input.\n");
        return -1;
    }

    srand(time(NULL));
    Snowflake snowflakes[NUM_SNOWFLAKES];
    for (int i = 0; i < NUM_SNOWFLAKES; i++) {
        init_snowflake(&snowflakes[i], 0, width, height);
    }

    int running = 1;
    int current_background = 0;
    int is_touch_active = 0;

    while (running) {
        struct input_event ev;
        while (libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev) == 0) {
            if (ev.type == EV_ABS) {
                if (ev.code == ABS_X || ev.code == ABS_Y) {
                    if (!is_touch_active) {
                        current_background = (current_background + 1) % num_backgrounds;
                        is_touch_active = 1;
                    }
                }
            } else if (ev.type == EV_SYN) {
                is_touch_active = 0;
            }
        }

        update_wind();
        SDL_RenderCopy(renderer, backgrounds[current_background], NULL, NULL);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < NUM_SNOWFLAKES; i++) {
            SDL_Rect rect = { snowflakes[i].x, snowflakes[i].y, snowflakes[i].size, snowflakes[i].size };
            SDL_RenderFillRect(renderer, &rect);
            update_snowflake(&snowflakes[i], width, height);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10); //Frames per second - increase for slower snow falling
    }

    for (int i = 0; i < num_backgrounds; i++) {
        SDL_DestroyTexture(backgrounds[i]);
    }
    free(backgrounds);
    libevdev_free(dev);
    close(fd);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
