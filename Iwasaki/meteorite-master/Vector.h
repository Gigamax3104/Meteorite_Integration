#pragma once
class Vector2
{
public:
	double x;
	double y;

	// コンストラクタ
	Vector2(double x, double y);
	Vector2();

	// 演算子オーバーロード
	Vector2 operator+(const Vector2& other)const;
	Vector2& operator+=(const Vector2& other);

	Vector2 operator-(const Vector2& other)const;
	Vector2& operator-=(const Vector2& other);

	Vector2 operator*(const Vector2& other)const;
	Vector2& operator*=(const Vector2& other);
	Vector2 operator*(const double k)const;
	Vector2& operator*=(const double k);

	Vector2 operator/(const Vector2& other)const;
	Vector2& operator/=(const Vector2& other);
	Vector2 operator/(const double k)const;
	Vector2& operator/=(const double k);

	bool operator==(const Vector2& other)const;
	bool operator!=(const Vector2& other)const;
	double Magnitude() const; // ベクトルの大きさを返す関数（sqrtを使っているため毎フレーム呼び出すのはNG）
	Vector2 Normalized() const; // 正規化
	double SqMagnitude() const; // ベクトルの大きさの二乗を返す関数

	static const Vector2 zero; // x:0 y:0
	static const Vector2 one; // x:1 y:1
	static const Vector2 up; // x:0 y:-1
	static const Vector2 down; // x:0 y:1
	static const Vector2 left; // x:-1 y:0
	static const Vector2 right; // x:1 y:0
	

};
double Vector2Distance(const Vector2& a, const Vector2& b); // 二点間の距離を返す関数（sqrtを使っているため毎フレーム呼び出すのはNG）
double Vector2DistanceSq(const Vector2& a, const Vector2& b); // 二点間の距離の二乗を返す関数

double Dot(const Vector2& a, const Vector2& b); // 内積の計算
double Cross(const Vector2& a, const Vector2& b); // 外積の計算


class Vector3
{
public:
	double x;
	double y;
	double z;

	// コンストラクタ
	Vector3(double x, double y, double z);
	Vector3();

	// 演算子オーバーロード
	Vector3 operator+(const Vector3& other)const;
	Vector3& operator+=(const Vector3& other);

	Vector3 operator-(const Vector3& other)const;
	Vector3& operator-=(const Vector3& other);

	Vector3 operator*(const Vector3& other)const;
	Vector3& operator*=(const Vector3& other);
	Vector3 operator*(const double k)const;
	Vector3& operator*=(const double k);

	Vector3 operator/(const Vector3& other)const;
	Vector3& operator/=(const Vector3& other);
	Vector3 operator/(const double k)const;
	Vector3& operator/=(const double k);

	bool operator==(const Vector3& other)const;
	bool operator!=(const Vector3& other)const;
	double Magnitude() const;  // ベクトルの大きさを返す関数（sqrtを使っているため毎フレーム呼び出すのはNG）
	Vector3 Normalized() const; // 正規化
	double SqMagnitude() const; //ベクトルの大きさの二乗を返す関数 

	static const Vector3 zero; // x:0 y:0 z:0
	static const Vector3 one; // x:1 y:1 z:1
	static const Vector3 up; // x:0 y:1 z:0
	static const Vector3 down; // x:0 y:-1 z:0
	static const Vector3 left; // x:-1 y:0 z:0
	static const Vector3 right; // x:1 y:0 z:0
	static const Vector3 forward; // x:0 y:0 z:1
	static const Vector3 back; // x:0 y:0 z:-1

};

double Vector3Distance(const Vector3& a, const Vector3& b); // 二点間の距離を返す関数（sqrtを使っているため毎フレーム呼び出すのはNG）
double Vector3DistanceSq(const Vector3& a, const Vector3& b); // 二点間の距離の二乗を返す関数

double Dot(const Vector3& a, const Vector3& b); // 内積の計算
Vector3 Cross(const Vector3& a, const Vector3& b); // 外積の計算


