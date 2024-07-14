#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Object/Camera.h"
#include "CharacterBase.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/AttackManager.h"
#include "../Object/Item/ItemBase.h"

//引数（マップの移動限界の中心、移動限界の半径）
class Player : public CharacterBase, public AttackManager{
private:
	//当たり判定用暑さ
	const float colli_thickness_ = 8.0f;
	//当たり判定の状態フラグ（true当たり判定有効、 false当たり判定無効）
	bool is_colli_ = true;
	//0以上なら無敵
	float invincible_ = 0.0f;
	//0以下なら攻撃できる
	float can_attack_ = 0.0f;
	//trueならプレイヤー表示
	bool is_flash_ = true;
	//無敵時間
	float invincible_time_ = 3.0f;
	//点滅間隔、点滅カウント
	float flash_interval_ = 0.25f, flash_count_ = 0.0f;
	//ダメージ時攻撃不能時間
	const float cooldown_time_ = 2.0f;

	//テクスチャ画像ハンドル
	Shared<dxe::Texture> texture_hdl_ = nullptr;
	//メッシュ配列の要素数
	static const int player_mesh_index_ = 3;
	//テクスチャ横分割数
	const int texture_div_ = 3; 
	//テクスチャ縦分割数
	const int texture_height_div_ = 4;
	//メッシュ
	Shared<dxe::Mesh> mesh_front_[player_mesh_index_];
	Shared<dxe::Mesh> mesh_left_[player_mesh_index_];
	Shared<dxe::Mesh> mesh_right_[player_mesh_index_];
	Shared<dxe::Mesh> mesh_back_[player_mesh_index_];
	
	//影のメッシュ
	Shared<dxe::Mesh> shadow_mesh_ = nullptr;
	//影のテクスチャ
	Shared<dxe::Texture> shadow_texture_ = nullptr;
	//90度倒す
	tnl::Quaternion shadow_down_ = tnl::Quaternion::RotationAxis({1,0,0}, tnl::ToRadian(90));
	//影のy座標
	const float shadow_pos_y_ = 0.1f;

	//通常攻撃の発射方向を示すカーソルのMesh
	Shared<dxe::Mesh> cursor_mesh_ = nullptr;
	//カーソルのテクスチャ
	Shared<dxe::Texture> cursor_texture_;
	//カーソルとプレイヤーの距離
	float distance_cursor_player_ = 20.0f;
	//カーソルの角度
	tnl::Quaternion cursor_rad_ = tnl::Quaternion();
	//カーソルの座標
	tnl::Vector3 cursor_pos_{ 0,0,0 };
	//カーソルを90度傾けるよう
	tnl::Quaternion cursor_down_ = tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(90));

	//マウスカーソルのレイと地面の当たった座標
	tnl::Vector3 ground_hit_pos_{ 0,0,0 };
	//ground_hit_pos_のパーティクル
	//Shared<dxe::Particle> attackcursor_ptcl_ = nullptr;

	//ステータスupのアイテムlist
	std::vector<ITEMTYPE> statusup_itemlist_;
	//アイテムlistの最大要素数
	const int itemmax_ = 5;
	//アイテムで変化するステータス
	struct ATTACKSTATUS {
		//攻撃移動速度
		float speed_attack_ = 0.0f;
		//生成間隔
		float interval_ = 0.0f;
		//攻撃力
		float power_ = 0.0f;
		//貫通力
		int Penetration_ = 0;
		//大きさ
		float size_scale_ = 1.0f;
		//プレイヤー移動速度
		float speed_player_ = 0.0f;
		//上がり幅
		float speed_attack_onerise_ = 5.0f;
		float interval_onerise_ = 0.07f;
		float power_onerise_ = 8.0f;
		int Penetration_onerise_ = 1;
		float size_scale_onerise_ = 0.25f;
		float speed_player_onerise_ = 1.5f;
	};
	ATTACKSTATUS itemupstatus_;
	const float little_up_ = 0.2f;

	//マップの地面のメッシュ
	Shared<dxe::Mesh> ground_ = nullptr;
	//カメラ
	Shared<Camera> camera_ = nullptr;

public:
	Player(tnl::Vector3 map_center = { 0,0,0 }, float map_rad = 500.0f, Shared<dxe::Mesh> ground = nullptr, Shared<Camera> camera = nullptr);
	~Player();
	//実行関数
	void Update(float delta_time) override;
	//プレイヤーの描画関数
	void Draw(float delta_time, std::shared_ptr<Camera> camera) override;
	//攻撃の描画
	void AttackDraw(std::shared_ptr<Camera> camera);

	//プレイヤー点滅
	void Flashing(float delta_tim, float flash_interval);
	//移動　
	//引数（delta_time, 移動出来るマップの中心、半径）
	void Move(float delta_time);
	//画面の中心からマウスカーソルの方向へのベクトルを正規化した値
	tnl::Vector3 Cursor_Move_Norm_();
	//画面中心からマウスカーソルへの角度（度数法）
	float Angle_Center_Mouse();
	//攻撃
	void Attack_Create(float delta_time);
	//敵と接触した時の処理
	void Enemy_Hit();
	//アイテムと接触した時の処理
	void Item_Hit(ITEMTYPE itemtype);
	//list内のアイテムを元に攻撃ステータス設定
	void AttackStatus_Set();

	//ステータスupアイテムのセッター
	void Setter_Item(ITEMTYPE& itemtype);
	//無敵状態フラグのゲッター
	bool Getter_is_colli()const { return is_colli_; };
	//描画フラグのゲッター
	bool Getter_is_flash_()const { return is_flash_; };
	//ステータスupのアイテムlistのゲッター
	std::vector<ITEMTYPE >& Getter_statusup_itemlist_() { return statusup_itemlist_; };
};

