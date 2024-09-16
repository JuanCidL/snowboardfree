from PIL import Image
import numpy as np
import struct
from os import path, listdir

# sprites folder path
SPRITES_PATH = path.join('resources', 'raw')
# data folder path
DATA_PATH = path.join('resources', 'data')

# function to convert a rgba[0-255] color to a rgba[0-1] color
def normalize_rgbacolor(color: tuple[int, int, int, int]) -> tuple[float, float, float, float]:
    return tuple([c / 255 for c in color])

def export_sprite(sprite: Image, name: str):
    # Get the colors from the image
    colors = sprite.getcolors()
    # Normalize the colors
    normalized_colors = [normalize_rgbacolor(color[1]) for color in colors]
    # Array pixels of the sprite
    pixels = np.array(sprite)
    # Dimensions
    width, height = sprite.size
    # Create a dictionary with the colors
    colors = {tuple(color): i for i, color in enumerate(normalized_colors)}

    # Write the data in a binary file
    with open (path.join(DATA_PATH, f'{name}.data'), 'w') as file:
        # Write quantity of colors and dimensions
        file.write(f'Color quantity: {len(normalized_colors)}\nWidth: {width}\nHeight: {height}\n')
        # Write the colors
        file.write('\nColors in RGBA:\n\n')
        for color in normalized_colors:
            file.write(f'{{ {color[0]}, {color[1]}, {color[2]}, {color[3]} }},\n')
        # Write the pixels
        file.write('\nPixel map:\n\n')
        file.write('{')
        for row in pixels:
            file.write('\n')
            for pixel in row:
                file.write(f'{str(colors[tuple(normalize_rgbacolor(pixel))])},')
        file.write('\n}')

if __name__ == '__main__':
    print('''Reading sprites names separated by spaces:''')

    # Read names of the sprites in stdin
    while True:
        try:
            names = input().split()
            break
        except EOFError:
            break

    # Read the sprites
    for name in names:
        print(f'Exporting {name} in {DATA_PATH} as {name}.data')
        sprite = Image.open(path.join(SPRITES_PATH, f'{name}.png'))
        export_sprite(sprite, name)