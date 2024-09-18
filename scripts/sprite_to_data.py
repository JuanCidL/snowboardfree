from PIL import Image
import numpy as np
from os import path

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

def export_sprite_sheet(sprite_sheet: Image, name: str, sprite_width: int, sprite_height: int):
    # Get the colors from the image
    colors = sprite_sheet.getcolors()
    # Normalize the colors
    normalized_colors = [normalize_rgbacolor(color[1]) for color in colors]
    # Array pixels of the sprite
    pixels = np.array(sprite_sheet)
    # Dimensions
    width, height = sprite_sheet.size
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
        # Write the pixels for each sprite
        file.write('\nPixel map:\n\n')
        sprite_count: int = pixels.shape[0] // sprite_height
        for i in range(sprite_count):
            # Write the sprite number
            file.write(f'Sprite {i}:\n')
            file.write('{')
            for row in pixels[i * sprite_height:(i + 1) * sprite_height]:
                file.write('\n')
                for pixel in row:
                    file.write(f'{str(colors[tuple(normalize_rgbacolor(pixel))])},')
            file.write('\n}')
            file.write('\n')

    

if __name__ == '__main__':
    print('Reading sprites names separated by spaces:')

    # Read names of the sprites in stdin
    while True:
        try:
            names = input().split()
            break
        except EOFError:
            break

    sprite_type = input('Enter the sprite type: (sprite or sprite_sheet in vertical): ')

    # Read the sprites
    for name in names:
        print(f'Exporting {name} in {DATA_PATH} as {name}.data')
        sprite = Image.open(path.join(SPRITES_PATH, f'{name}.png'))
        if sprite_type == 'sprite':
            export_sprite(sprite, name)
        elif sprite_type == 'sprite_sheet':
            sprite_width = int(input('Enter the sprite width: '))
            sprite_height = int(input('Enter the sprite height: '))
            export_sprite_sheet(sprite, name, sprite_width, sprite_height)
        else:
            print('Invalid sprite type')
            break