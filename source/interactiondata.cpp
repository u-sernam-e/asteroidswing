#include "interactiondata.h"

void initID(InteractionData& id)
{
	initBD(id.bd);

	PolyLightShader::init(id.PLShad);
}

void updateID(InteractionData& id)
{
	updateBD(id.bd);
}

void drawID(InteractionData& id)
{
	drawBD(id.bd);
}