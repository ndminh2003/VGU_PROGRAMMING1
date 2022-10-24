#include <math.h>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"

unsigned char *uc_arrayNew_1d(int _size)
{
    return (unsigned char *)calloc(_size, sizeof(unsigned char));
}

unsigned char *sub_image(unsigned char *image1, unsigned char *image2, unsigned char *image3, int width, int height, int channel)
{
    unsigned char *temp_array = uc_arrayNew_1d(width * height * channel);
    unsigned char *temp_array1 = uc_arrayNew_1d(width * height * channel);
    int temp=0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

                for (int k = 0; k < channel; k++)
                {
                    temp = image2[i * width * channel + j * channel + k] - image1[i * width * channel + j * channel + k];
                    temp = abs(temp);
                    if ((temp<35)) {
                        temp_array[i * width * channel + j * channel + k] = image2[i * width * channel + j * channel + k];
                    }
                }
                for (int k = 0; k < channel; k++)
                {
                    if (k==0&&(temp_array[i * width * channel + j * channel + k]!=0)) {
                        temp_array[i * width * channel + j * channel + k] = 0;
                    }
                    if (k==2&&(temp_array[i * width * channel + j * channel + k]!=0)) {
                        temp_array[i * width * channel + j * channel + k] = 0;
                    }

                }
                for (int k = 0; k < channel; k++)
                {
                    temp_array1[i * width * channel + j * channel + k] = 255;

                }
                for (int k = 0; k < 3; k++)
                {
                    if (temp_array[i * width * channel + j * channel + 1]==temp_array[i * width * channel + j * channel + 2]&&temp_array[i * width * channel + j * channel + 2]==temp_array[i * width * channel + j * channel + 3])
                        temp_array1[i * width * channel + j * channel + k] = temp_array[i * width * channel + j * channel + k];

                }
                for (int k = 0; k < channel; k++)
                {
                    if (temp_array1[i * width * channel + j * channel + k]==255)
                        temp_array1[i * width * channel + j * channel + k] = image3[i * width * channel + j * channel + k];
                    else
                        temp_array1[i * width * channel + j * channel + k] = image2[i * width * channel + j * channel + k];

                }

        }
    }
    return temp_array1;
}

int main()
{
    // declare variables
    int width, height, channel;
    int width1, height1, channel1;
    int width2, height2, channel2;
    char path_img_background[] = "./images/background.png";
    char path_img_foreground[] = "./images/foreground.png";
    char path_img_wall[] = "./images/weather_forecast.jpg";
    char save_path[] = "./images/New.png";

    // read image data
    unsigned char *image1 = stbi_load(path_img_background, &width, &height, &channel, 0);
    if (image1 == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    unsigned char *image2 = stbi_load(path_img_foreground, &width1, &height1, &channel1, 0);
    if (image2 == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    unsigned char *image3 = stbi_load(path_img_wall, &width2, &height2, &channel2, 0);
    if (image3 == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    printf("Width = %d\nHeight = %d\nChannel = %d\n", width, height, channel);
    printf("Width = %d\nHeight = %d\nChannel = %d\n", width1, height1, channel1);
    printf("Width = %d\nHeight = %d\nChannel = %d\n", width2, height2, channel2);
    // fill a quarter of the image with black pixels
    unsigned char *mimage = sub_image(image1,image2,image3, width, height, channel);
    stbi_write_png(save_path, width, height, channel, mimage, width * channel);
    printf("New image saved to %s\n", save_path);
}
