#include<iostream>
#include<SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "imgui.h"
#include "imgui-sfml.h"
#include<string>
#include <cstdlib> // rand, srand
#include <ctime>
#include <optional>
#include <SFML/System.hpp>
//为保证能运行，注释掉了imgui-SFML.cpp第956行的：“assert(io.Fonts->TexID != (ImTextureID) nullptr); ”，没懂为什么出问题，先这样先。
sf::Font font;
class object {
protected:
	std::string Name;
	sf::Vector2f p;
	sf::Vector2f v;
	sf::Color color;
	sf::Text text;
	float textX;
	float textY;
public:
	object(const object&) = delete;
	object& operator=(const object&) = delete;
	object(std::string a,sf::Vector2f c,sf::Color d,sf::Font& font)
		 :Name(a), p(0.f, 0.f), v(c),color(d), textX(0.f), textY(0.f),text(font, Name, 20)
	{
		text.setFont(font);
		text.setFillColor(sf::Color::White);
		text.setString(Name);
		text.setCharacterSize(20);
		////由于一帧时间太短了，这下面这段对视觉效果毫无影响
		//sf::FloatRect textRect = text->getLocalBounds();
		//float textX = p.x - (textRect.size.x / 2.0f);
		//float textY = p.y - (textRect.size.y / 2.0f);

		//text->setPosition(sf::Vector2f(textX + R, textY + R));
		////由于一帧时间太短了，这上面这段对视觉效果毫无影响
	}
	object()
		:Name(""), p(0.f, 0.f), v(10.f, 10.f),color(255,0,0), textX(0.f), textY(0.f), text(font, Name, 20)
	{
	}
	virtual void sport()
	{
		p.x += v.x;
		p.y += v.y;
	}
	virtual void draw(sf::RenderWindow& window)
	{
		window.draw(text);
	}
	/*virtual void drawbutton()
	{
		ImVec2 windowspos = ImGui::GetCursorScreenPos();
		float x = windowspos.x +1;
		float y = windowspos.y +1;
		ImGui::SetCursorScreenPos(ImVec2(x,y));
	}*/
	//这里原定想实现点击物体后能修改物体属性的功能，最后放弃了。整体思路是要建造一个虚拟满屏imgui窗口，然后在物体上放一个隐形的按钮，
	// 导致点击能锁定该物体。
	//还有个planB是直接改combo对应的shape，然后基于这个shape做一个类似函数的“if大合集”，实现修改效果。有大体思路，但不准备上手敲了，
	// 因为这个代码已经写了一天多了，不能在这做太久，先往后看了。还要留时间研究怎么传github呢。

};
class circle: public object {
private:
	float R;
	sf::CircleShape Circle;
public:
	circle(std::string a, sf::Vector2f c, sf::Color d, float e, sf::Font& font)
		: object(a, c, d, font), R(e),Circle(R)
	{
		Circle.setPosition(p);
		Circle.setFillColor(color);
	}
	circle()
		:object(),R(10),Circle(R)
	{
		Circle.setPosition(p);
		Circle.setFillColor(color);
	}
	void sport() override
	{
		object::sport();
		if (p.x < 0)
		{
			v.x = -v.x;
			p.x = 0;
			Circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
		}
		if (p.x + 2 * R > 800)
		{
			v.x = -v.x;
			p.x = 800 - 2 * R;
			Circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
		}
		if (p.y < 0)
		{
			v.y = -v.y;
			p.y = 0;
			Circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
		}
		if (p.y + 2 * R > 600)
		{
			v.y = -v.y;
			p.y = 600 - 2 * R;
			Circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
		}
		sf::FloatRect textRect = text.getLocalBounds();
		float textX = p.x - (textRect.size.x / 2.0f - R);
		float textY = p.y - (textRect.size.y / 2.0f - R);

		text.setPosition(sf::Vector2f(textX, textY));
		Circle.setPosition(p);
	}
	void draw(sf::RenderWindow& window) override
	{
		window.draw(Circle);
		object::draw(window);
		//drawbutton();
	}
	//void drawbutton()
	//{
	//	object::drawbutton();
	//}

};
class rec : public object
{
private:
	float A;
	float B;
	sf::RectangleShape Rec;
public:
	rec(std::string a, sf::Vector2f c, sf::Color d, float e,float f, sf::Font& font)
		: object(a, c, d, font), A(e), B(f),Rec({A,B})
	{
		Rec.setPosition(p);
		Rec.setFillColor(color);
	}
	rec()
		:object(), A(10),B(20), Rec({A,B})
	{
		Rec.setPosition(p);
	    Rec.setFillColor(color);
	}
	void sport() override
	{
		object::sport();
		if (p.x < 0)
		{
			v.x = -v.x;
			p.x = 0;
			Rec.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
		}
		if (p.x + A > 800)
		{
			v.x = -v.x;
			p.x = 800 - A;
			Rec.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
		}
		if (p.y < 0)
		{
			v.y = -v.y;
			p.y = 0;
			Rec.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
		}
		if (p.y +  B > 600)
		{
			v.y = -v.y;
			p.y = 600 - B;
			Rec.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
		}
		sf::FloatRect textRect = text.getLocalBounds();
		float textX = p.x - (textRect.size.x / 2.0f - A/2);
		float textY = p.y - (textRect.size.y / 2.0f - B/2);

		text.setPosition(sf::Vector2f(textX, textY));
		Rec.setPosition(p);
	}
	void draw(sf::RenderWindow& window) override
	{
		window.draw(Rec);
		object::draw(window);
		//drawbutton();
	}
	//void drawbutton()
	//{
	//	object::drawbutton();
	//}
};
int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	unsigned int w = 800;
	unsigned int h = 600;
	sf::RenderWindow window(sf::VideoMode({ 800,600 }), L"碰撞游戏");
	window.setFramerateLimit(60);
	if (!ImGui::SFML::Init(window))
	{
		std::cout << "未能成功初始化" << std::endl;
		exit(-1);
	}
	sf::Clock clock;
	ImGui::GetStyle().ScaleAllSizes(2.0f);
	ImGui::GetIO().FontGlobalScale=2.0f;
	if (!font.openFromFile("font-arial/arial.ttf"))
	{
		std::cout << "载入字体失败" << std::endl;
		exit(-1);
	}
	if (!ImGui::SFML::UpdateFontTexture()) {
		std::cerr << "致命错误：字体纹理上传显卡失败！检查 SFML 3.0 配置。" << std::endl;
	}
	circle a;
	circle b1("smallcircle", { 3.f,3.f }, { 100,100,100 }, 100, font);
	circle b2("bigcircle", { 3.7f,3.7f }, { 187,0,0}, 85, font);
	circle b3("hugecircle", { 6.2f,6.1f }, { 0,155,0 }, 36, font);
	rec c;
	rec d1("smallrec", { 5.f,5.f }, { 187,0,132 }, 110,220, font);
	rec d2("bigrec", { 3.5f,3.5f }, { 187,155,0 }, 150, 150, font);
	rec d3("hugerec", { 8.f,8.f }, { 0,155,132 }, 60, 90, font);
	clock.restart();
	while (window.isOpen ())
	{
		/*sf::Event event;
		while (window.pollEvent(event));*/
		//sfml3.0改革了event的用法，不能像视频里一样使用了
		while (const std::optional<sf::Event> event = window.pollEvent())
		{
			ImGui::SFML::ProcessEvent(window,*event);
			if (event->is<sf::Event::Closed>())
				window.close();
		}
		ImGui::SFML::Update(window, clock.restart());
		ImGui::Begin("shape properties");
		if (ImGui::CollapsingHeader("setting", ImGuiTreeNodeFlags_DefaultOpen))
		{
			const char* shape[] = { "circle","rectangle"};
			static int current_shape = 0;
			ImGui::Combo("shape", &current_shape, shape, IM_ARRAYSIZE(shape));
			static bool drawshape = true;
			ImGui::Checkbox("drawshape", &drawshape);
			static float slide = 1.0f;
			ImGui::SliderFloat("slide", &slide, 0.0f, 4.0f);
			static float velocity[2] = { 10.0f,10.0f };
			ImGui::InputFloat2("velocity", velocity);
			static float color1[3] = { 0.0f,0.0f,0.0f };
			ImGui::ColorEdit3("color", color1);
			static char name[18] = {};
			ImGui::InputText("name", name, IM_ARRAYSIZE(name));
		}
		a.sport();
		b1.sport();
		b2.sport();
		b3.sport();
		c.sport();
		d1.sport();
		d2.sport();
		d3.sport();
		window.clear();
		a.draw(window);
		b1.draw(window);
		b2.draw(window);
		b3.draw(window);
		c.draw(window);
		d1.draw(window);
		d2.draw(window);
		d3.draw(window);
		ImGui::End();
		ImGui::SFML::Render(window);
		window.display();
	}
	return 0;
}