# Image Converter to oled display ssd1306 128x64
## How does it works:
Basically the algorithm should take an image and return optimazed hex array with full code ready to copy and put into Arduino IDE<br>
By now algorithm pass bitmap array tests.
## To do:
• GUI app which returns an easy and optimazed code that is ready to put into Arduino(updated)
## What is done:
• Read and open image file<br>
• Resize any photo to 128x64 and then to ASCII(updated)<br>
• Convertion transparent pixels and not transparent pixels to 0 and 1 Ascii representation<br>
• 8-bit to one byte conversion<br>
• Output as full hexa bitmap array <br>
• Return full copyable code to insert to Arduino IDE<br>
• Conver jpg to ppm(deleted in order to speed up the code)<br>
• Binary to hexa convertion(deleted->updated)<br>
## What I learned:
• Fstream library<br>
• Working with file and image<br>
• Bitmap image structure<br>
• Basic of OpenCV library<br>
