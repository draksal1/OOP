<h1>BMP resolution</h1>

Implement a class to get information about the size of an image in a BMP file with the following assumption. If the file name ends with _WWWWxHHHH, where WWW and HHH are decimal numbers (not necessarily consisting of three digits), then WWW is the width and HHH is the height of the image. In this case it is not necessary to open the file to get the size.

    vasya_1024x768.bmp - size 1024x768.
    kolya_300x30 - size 30x30.
    petya_200xmax.bmp - wrong format.

In the latter case, since the format does not match, the module should still open the BMP file and read the size explicitly.

Work with the BMP-file itself should be placed in a separate class (you can use the Bitmap class). The created class should encapsulate it (composition relation). 

https://oop.afti.ru/task_assignments/5458
