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
    with open (path.join(DATA_PATH, f'{name}.data'), 'wb') as file:
        # Write quantity of colors and dimensions
        file.write(struct.pack('IHH', len(normalized_colors), width, height))
        # Write the colors
        for color in normalized_colors:
            file.write(struct.pack('4f', *color))
        # Write the pixels
        for row in pixels:
            file.write(b'\n')
            for pixel in row:
                file.write(struct.pack('B', colors[tuple(normalize_rgbacolor(pixel))]))

def read_data_file(name: str):
    with open(path.join(DATA_PATH, f'{name}.data'), 'rb') as file:
        # Read quantity of colors and dimensions
        colors, width, height = struct.unpack('IHH', file.read(8))
        # Read the colors
        color_list = [struct.unpack('4f', file.read(16)) for _ in range(colors)]
        # Read the pixels
        pixels = np.array([[struct.unpack('B', file.read(1))[0] for _ in range(width)] for _ in range(height)])
        # print all the data
        print(f'Colors: {colors}\nWidth: {width}\nHeight: {height}\nColor list: {color_list}\nPixels: {pixels}')

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
        # read_data_file(name)
        print(f'Exporting {name} in {DATA_PATH} as {name}.data')
        sprite = Image.open(path.join(SPRITES_PATH, f'{name}.png'))
        export_sprite(sprite, name)