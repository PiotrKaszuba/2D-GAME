#include "Column.h"



Column::Column()
{
}

Column::Column(int ID, Sprite_Sheet_Data base, sf::Vector2f position, World<Physical>* mapa, bool hint_truth,sf::Vector3<char> hint, dependance hint_type) : Usable(ID, base, position, mapa)
{
	this->hint.x = hint.x;
	this->hint.y = hint.y;
	this->hint.z = hint.z;
	this->hint_lifetime = 0;
	this->hint_display.setFont(*mapa->get_font());
	this->hint_type = hint_type;
	this->hint_truth = hint_truth;
	if (this->hint_truth)
		this->hint_display.setFillColor(sf::Color::Green);
	else 	
		this->hint_display.setFillColor(sf::Color::Red);
	if (this->hint_type == sum_higher)
		this->a = '>';
	if (this->hint_type == sum_lower)
		this->a = '<';
	if (this->hint_type == divisibility)
		this->a = '|';
	if (this->hint_type == does_not_contain)
		this->a = '?';
	if (this->hint_type == permutation)
		this->a = '!';
}

void Column::useit(Physical * user)
{
	this->hint_lifetime = 100;
}

void Column::update(World<Physical>* mapa)
{
	this->Animate();
	mapa->draw(*this);
	this->hint_display_update(mapa);
}
void Column::hint_display_update(World<Physical>* mapa)
{
	if (this->hint_lifetime != 0)
	{
		this->hint_display.setString(std::string(1, a).append(std::to_string(int(this->hint.x)).append(std::to_string(int(this->hint.y)).append(std::to_string(int(this->hint.z))))));
	
		this->hint_display.setPosition(this->getPosition().x - 36.f, this->getPosition().y - float(this->height) / 2 - float(this->sprite_sheet_animation_num[this->animated_state].Get_type_of_animation_size_modifier().y * this->getScale().y) / 2 - 30.f);
	
		mapa->draw(this->hint_display);
		this->hint_lifetime -= 1;
	}
}

Column::~Column()
{
}
