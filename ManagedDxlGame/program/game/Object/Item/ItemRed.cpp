#include "ItemRed.h"

ItemRed::ItemRed(int& mv1model) : ItemBase(mv1model){
	//タイプ設定
	itemtype_ = ITEMTYPE::Red;
}

ItemRed::~ItemRed(){

}
