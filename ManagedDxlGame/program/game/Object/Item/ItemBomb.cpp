#include "ItemBomb.h"

ItemBomb::ItemBomb(int& mv1model) : ItemBase(mv1model){
	//タイプ設定
	itemtype_ = ITEMTYPE::Bomb;
}

ItemBomb::~ItemBomb(){

}

void ItemBomb::Update(float delta_time){
	__super::Update(delta_time);
}
