#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

double benzerlikhesapla(const Mat& image1, const Mat& image2) {
    Mat hist1, hist2 ;

    int histSize = 256; //histogram boyutu
    float range[] = { 0,256 }; //piksel aralýðý
    const float* histRange = { range };
    bool uniform = true;
    bool accumulate = false;

    // resimlerin histogramýný hesapla
    calcHist(&image1, 1, 0, Mat(), hist1, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&image2, 1, 0, Mat(), hist2, 1, &histSize, &histRange, uniform, accumulate);

    // histogramlarý normalleþtir
    normalize(hist1, hist1, 0, 1, NORM_MINMAX, -1, Mat());
    normalize(hist2, hist2, 0, 1, NORM_MINMAX, -1, Mat());

    // Histogram kesiþme yöntemini kullanarak histogramlar arasýndaki benzerliði hesaplayýn
    double similarity = compareHist(hist1, hist2, HISTCMP_INTERSECT);

    return similarity;
}

int main() {
    string folderPath = "C:\\Users\\ASUS\\Desktop\\AATKS2.2\\gorseller";  // Klasör yolunu buraya gir
    int numImages = 150;  // Klasördeki toplam görüntü sayýsý

    vector<string> imagePaths;
    for (int i = 1; i <= numImages; i++) {
        string imagePath = folderPath + "/" + to_string(i) + ".png";  // Görüntü dosyasýnýn yolunu oluþtur
        imagePaths.push_back(imagePath);
    }

    vector<pair<string, string>> similarImages;
    for (int i = 0; i < numImages; i++) {
        Mat image1 = imread(imagePaths[i]);  // Ýlk görüntüyü yükle

        double maxSimilarity = 0.0;
        string mostSimilarImage;

        for (int j = i + 1; j < numImages; j++) {
            Mat image2 = imread(imagePaths[j]);  // Ýkinci görüntüyü yükle

            double similarity = benzerlikhesapla(image1, image2);  // Benzerliði hesapla

            if (similarity > maxSimilarity) {
                maxSimilarity = similarity;
                mostSimilarImage = imagePaths[j];
            }
        }

        if (maxSimilarity > 0.0) {
            similarImages.push_back(make_pair(imagePaths[i], mostSimilarImage));
        }
    }

    // Benzer görüntüleri listele
    cout << "En çok benzeyen görüntüler:" << endl;
    for (const auto& pair : similarImages) {
        cout << pair.first << " ve " << pair.second << endl;
    }

    return 0;
}
