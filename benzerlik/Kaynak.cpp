#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

double benzerlikhesapla(const Mat& image1, const Mat& image2) {
    Mat hist1, hist2 ;

    int histSize = 256; //histogram boyutu
    float range[] = { 0,256 }; //piksel aral���
    const float* histRange = { range };
    bool uniform = true;
    bool accumulate = false;

    // resimlerin histogram�n� hesapla
    calcHist(&image1, 1, 0, Mat(), hist1, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&image2, 1, 0, Mat(), hist2, 1, &histSize, &histRange, uniform, accumulate);

    // histogramlar� normalle�tir
    normalize(hist1, hist1, 0, 1, NORM_MINMAX, -1, Mat());
    normalize(hist2, hist2, 0, 1, NORM_MINMAX, -1, Mat());

    // Histogram kesi�me y�ntemini kullanarak histogramlar aras�ndaki benzerli�i hesaplay�n
    double similarity = compareHist(hist1, hist2, HISTCMP_INTERSECT);

    return similarity;
}

int main() {
    string folderPath = "C:\\Users\\ASUS\\Desktop\\AATKS2.2\\gorseller";  // Klas�r yolunu buraya gir
    int numImages = 150;  // Klas�rdeki toplam g�r�nt� say�s�

    vector<string> imagePaths;
    for (int i = 1; i <= numImages; i++) {
        string imagePath = folderPath + "/" + to_string(i) + ".png";  // G�r�nt� dosyas�n�n yolunu olu�tur
        imagePaths.push_back(imagePath);
    }

    vector<pair<string, string>> similarImages;
    for (int i = 0; i < numImages; i++) {
        Mat image1 = imread(imagePaths[i]);  // �lk g�r�nt�y� y�kle

        double maxSimilarity = 0.0;
        string mostSimilarImage;

        for (int j = i + 1; j < numImages; j++) {
            Mat image2 = imread(imagePaths[j]);  // �kinci g�r�nt�y� y�kle

            double similarity = benzerlikhesapla(image1, image2);  // Benzerli�i hesapla

            if (similarity > maxSimilarity) {
                maxSimilarity = similarity;
                mostSimilarImage = imagePaths[j];
            }
        }

        if (maxSimilarity > 0.0) {
            similarImages.push_back(make_pair(imagePaths[i], mostSimilarImage));
        }
    }

    // Benzer g�r�nt�leri listele
    cout << "En �ok benzeyen g�r�nt�ler:" << endl;
    for (const auto& pair : similarImages) {
        cout << pair.first << " ve " << pair.second << endl;
    }

    return 0;
}
