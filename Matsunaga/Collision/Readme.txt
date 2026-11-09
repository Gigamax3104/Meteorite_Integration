当たり判定用関数が入った名前空間です。
すべてboolで当たっていたらtrueを返します。

関数
bool PointAndCircle(Vector2 点の位置, Vector2 円の位置, double 円の半径); // 点の円の当たり判定
bool PointAndRect(Vector2 点の位置, Vector2 矩形の位置, Vector2 矩形のサイズ); // 点と矩形の当たり判定
bool CircleAndCircle(Vector2 円Aの位置, double 円Aの半径, Vector2 円Bの位置, double 円Bの半径); // 円と円の当たり判定
bool RectAndRect(Vector2 矩形Aの位置, Vector2 矩形Aのサイズ, Vector2 矩形Bの位置, Vector2 矩形Bのサイズ); // 矩形と矩形の当たり判定

使い方
①
Vector2クラスが必要です。
Collision.hを開いて一番上に"Vector.h"をインクルードをしてください。

②
使いたいcppファイルで"Collision.h"をインクルード

<点と円の当たり判定を行いたい場合>

Vector2 pointPos;
Vector2 circlePos;
double circleRadius;
if(Collision::PointAndCircle(pointPos, circlePos, circleRadius))
{
	当たった場合の処理など
}
else
{
	当たっていない場合の処理など
}

