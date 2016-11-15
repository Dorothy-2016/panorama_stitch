/*************************************************
* PanoScript��
* ��ȡPanoStitcher�ű����õ�remapping���N·��Ƶ�����б任��
*************************************************/
#pragma once
#include <vector>
#include <string>

enum
{                               // Enumerates for Image.format
	_rectilinear = 0,           // (Standand) FOV (rectilinear) =  2 * arctan (frame size/(focal length * 2))
	_panorama = 1,              // Cylindrical
	_fisheye_circ = 2,          // fisheye-equidistance Circular
	_fisheye_ff = 3,            // fisheye-equidistance Full Frame
	_equirectangular = 4,
	_spherical_cp = 5,          // Fisheye-Horizontal is an image shot with the camera held horizontally. The equator is now in the center of the image.
	_spherical_tp = 6,          // Fisheye-vertical is an image shot with the camera held vertically up.  The panorama is extracted from the circumpherence of the image. 
	_mirror = 7,                // convex mirror. This is the reflection of a convex, spherical image. The horizontal field of view is calculated using the formula HFov = 2*arcsin(radius of mirror/radius of curvature of mirror)
	_orthographic = 8,          // fisheye-orthographic FOV  (orthogonal fisheye) = 2 * arcsin (frame size/(focal length *2)
	_cubic = 9,
	_stereographic = 10,        // fisheye stereographic FOV (stereographic fisheye) = 4 * arctan (frame size/(focal length * 4))
	_mercator = 11,
	_trans_mercator = 12,
	_trans_panorama = 13,
	_sinusoidal = 14,
	_lambert = 15,
	_lambertazimuthal = 16,
	_albersequalareaconic = 17,
	_millercylindrical = 18,
	_panini = 19,
	_architectural = 20,
	_equisolid = 21,          // fisheye-equisolid  FOV (equisolid fisheye) = 4 * arcsin (frame size/(focal length * 4))
	_equipanini = 22,
	_biplane = 23,
	_triplane = 24,
	_panini_general = 25,
	_thoby = 26,             // generalizes the model found in modern fisheye lenses. It is
	// parametrizable but it defaults to the Nikkor 10.5 fisheye lens
	_hammer = 27,
};

class PanoScript {
public:
	struct PanoParam { // ��¼����ȫ��ͼ�Ĳ�����
		int w, h; // ����ȫ��ͼ�Ŀ�ȣ��߶�
		double hfov; // ����ȫ��ͼ����Ұ��Χ��1~360��
	};

	struct ImageParam { // ��¼ÿ·��Ƶ֡�Ĳ���
		ImageParam();
		int w, h, f; // ֡��ȣ��߶ȣ�����
		int S[4], C[4]; // ���ò����� select��crop
		double hfov; // ֡����Ұ��Χ��1~360��
		double roll, pitch, yaw; // �����������ת�Ƕ�
		double g, t;
		double rad[6], hori, vert; // ����У����ƫ��У��
		bool radial, horizontal, vertical, select, crop; // ��¼�Ƿ���ĳЩƫ��
		PanoParam* pano; // ��Ӧ��ȫ��ͼ����
	};

	struct TransParam { // ��¼�任�Ĳ���
		double distance;
		double rot[2];
		double scale[2];
		double mt[3][3];
		double rad[6], horizontal, vertical;
		void * perspect[2];
	};
public:
	PanoScript(std::string);
	~PanoScript();
public:
	void readPanoLine(std::string);
	void readImageLine(std::string, int);
	void loadScript(std::string);


	void setTransPram(int);
	void transform(double, double, double*, double*);
	void getROI();
public:
	PanoParam pano;
	std::vector<ImageParam> images;
	TransParam trans;
	ImageParam* curImagePtr;
};