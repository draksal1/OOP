#include "gtest/gtest.h"
#include "ImageSizeExtractor.h"
#include <fstream>


TEST(ImageSizeExtractorTest, SuchFule)
{
	EXPECT_THROW(ImageSizeExtractor(std::string("  ")), std::invalid_argument);
}

TEST(ImageSizeExtractorTest, tittleTest)
{
	ImageSizeExtractor test(std::string("_1024x1025.bmp"));
	ImageSizeExtractor test1(std::string("_10x25.bmp"));
	ImageSizeExtractor test2(std::string("_1024432x1025123.bmp"));
	EXPECT_EQ(test.getHeight(), 1025);
	EXPECT_EQ(test.getWidth(), 1024);

	EXPECT_EQ(test1.getHeight(), 25);
	EXPECT_EQ(test1.getWidth(), 10);

	EXPECT_EQ(test2.getHeight(), 1025123);
	EXPECT_EQ(test2.getWidth(), 1024432);
}


TEST(ImageSizeExtractorTest, WrongtittleTest)
{
	EXPECT_THROW(ImageSizeExtractor test(std::string("File_5xx10.bmp")), std::invalid_argument);
	EXPECT_THROW(ImageSizeExtractor test1(std::string("File_5x10x.bmp")), std::invalid_argument);
	EXPECT_THROW(ImageSizeExtractor test2(std::string("File_e5x10.bmp")), std::invalid_argument);
	EXPECT_THROW(ImageSizeExtractor test3(std::string("File_5x10x20.bmp")), std::invalid_argument);
}

TEST(ImageSizeExtractorTest, TempFilesTest) {
	std::filesystem::path tempPath = std::filesystem::temp_directory_path() / "bitmap_proxy_temp";
	std::filesystem::create_directories(tempPath);

	BitmapEx first(800, 600);
	first.save((tempPath / "first.bmp").string());
	BitmapEx second(1, 1);
	second.save((tempPath / "second.bmp").string());
	BitmapEx third(20, 30);
	third.save((tempPath / "third.bmp").string());

	ImageSizeExtractor test1((tempPath / "first.bmp").string());
	ImageSizeExtractor test2((tempPath / "second.bmp").string());
	ImageSizeExtractor test3((tempPath / "third.bmp").string());
	EXPECT_TRUE((test1.getHeight() == 600) && (test1.getWidth() == 800));
	EXPECT_TRUE((test2.getHeight() == 1) && (test2.getWidth() == 1));
	EXPECT_TRUE((test3.getHeight() == 30) && (test3.getWidth() == 20));

	std::filesystem::remove_all(tempPath);
}


TEST(ImageSizeExtractorTest, WrongtittleTestWithExisting)
{
	std::filesystem::path tempPath = std::filesystem::temp_directory_path() / "bitmap_proxy_temp";
	std::filesystem::create_directories(tempPath);
	BitmapEx test(100, 100);
	test.save((tempPath / "File_5xxx10.bmp").string());
	ImageSizeExtractor test1((tempPath / "File_5xxx10.bmp").string());
	EXPECT_EQ(test1.getHeight(), 100);
	EXPECT_EQ(test1.getWidth(), 100);
	std::filesystem::remove_all(tempPath);
}


TEST(ImageSizeExtractorTest, CoorectTittleExistingFileDiffierentSize)
{
	//Файл существует, название корректное, но размеры, указанные в названии и в файле отличаются
	//Мы "доверем", что в названии всегда правда, так что файл не открываем и не проверяем правильность
	std::filesystem::path tempPath = std::filesystem::temp_directory_path() / "bitmap_proxy_temp";
	std::filesystem::create_directories(tempPath);
	BitmapEx test(100, 100);
	test.save((tempPath / "File_150x150.bmp").string());
	ImageSizeExtractor test1((tempPath / "File_150x150.bmp").string());
	EXPECT_EQ(test1.getHeight(), 150);
	EXPECT_EQ(test1.getWidth(), 150);
	std::filesystem::remove_all(tempPath);
}

TEST(ImageSizeExtractorTest, UnderscopeTest)
{
	ImageSizeExtractor test(std::string("File_1x2_5x10.bmp"));
	EXPECT_EQ(test.getHeight(), 10);
	EXPECT_EQ(test.getWidth(), 5);
}


TEST(ImageSizeExtractorTest, UncorrectExistence)
{
	std::filesystem::path tempPath = std::filesystem::temp_directory_path() / "bitmap_proxy_temp";
	std::filesystem::create_directories(tempPath);
	BitmapEx test(100, 100);
	test.save((tempPath / "File_5xxx10.jpg").string());
	EXPECT_THROW(ImageSizeExtractor test1((tempPath / "File_5xxx10.jpg").string()), std::invalid_argument);
	std::filesystem::remove_all(tempPath);
}


TEST(ImageSizeExtractorTest, ExistingNotBmpButWithBmpTittle)
{
	std::filesystem::path tempPath = std::filesystem::temp_directory_path() / "bitmap_proxy_temp";
	std::filesystem::create_directories(tempPath);
	std::filesystem::path filePath = tempPath / "test_file.bmp";
	std::ofstream file(filePath);
	EXPECT_THROW(ImageSizeExtractor test1((filePath).string()), std::invalid_argument);
	file.close();
	std::filesystem::remove_all(tempPath);
}