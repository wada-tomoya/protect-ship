#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "../../Object/Camera.h"
#include "ItemBase.h"

class ItemBomb : public ItemBase {
private:


public:
	ItemBomb(int& mv1model);
	~ItemBomb();

	//���s�֐�
	void Update(float delta_time)override;
};