#include <stdio.h>
#include <SFML/Graphics.hpp>//Подключение заголовочного файла который работает с шрафикой 

using namespace sf;

const int M = 20;//высота игрового поля
const int N = 10;//ширина игрового поля

int  field[M][N] = { 0 };//игравое роле

//Массив фигурок
int  figures[7][4] = {//7 - фигур, фигура состоит из 4х - малениких элементов
  1, 3, 5, 7,//"I"
  2, 4, 4, 7,//"S"
  3, 5, 4, 6,//"Z"
  3, 5, 4, 7,//"T"
  2, 3, 5, 7,//"L"
  3, 5, 6, 7,//"J"
  2, 3, 4, 5,//"O"
};

struct Point {
	int x, y;
}

a[4], b[4];

int main() {
// Объект, который, собственно, является главным окном приложения
RenderWindow window(VideoMode(320, 480), "The game");

// Создаём переменную текстуры
Texture texture;

// Подгружаем нашу текстуру из файла texture.png
texture.loadFromFile("D:\\junioC++\\TEST\\SFML\\images\\img.png");

// Создаём спрайт и устанавливаем ему нашу текстуру
Sprite sprite(texture);

//Вырезаем  отдельный квадрат 18х18 пикселей
sprite.setTextureRect(IntRect(0, 0, 18, 18));

int dx = 0; //переменная для горизонтал перемещения
bool rotate = 0;//переменная для вращения тетрамино

//Переменная для таймера и задержки
float timer = 0, delay = 0.3;

//Часы (таймер)
Clock clock;

// Главный цикл приложения. Выполняется, пока открыто окно
while (window.isOpen()) {

  //Посколько время, прошедшее с начала отсчета , конвертируем в секунду 
  float time = clock.getElapsedTime().asSeconds();
  clock.restart();
  timer += time;

  // Обрабатываем очередь событий в цикле
  Event event;
  while (window.pollEvent(event)) {
	
    // Пользователь нажал на «крестик» и хочет закрыть окно?
	if (event.type == Event::Closed)
	  // Тогда закрываем его
	  window.close();

	//отлавливаем события нажата  ли клавиша на клавиатуре
	if (event.type == Event::KeyPressed)
	  //эта кнопка "стрелка вверх" 
	  if (event.key.code == Keyboard::Up)
	    rotate = true;
	  //эта кнопка  "стрелка влево"
	  else if  (event.key.code == Keyboard::Left) 
		dx = -1; //делаем шаг в лево
	//эта кнопка  "стрелка влево"
	  else if (event.key.code == Keyboard::Right) 
		dx = 1; //делаем шаг в право
  }

  //Горизонтальное перемещение(сдвигаем все части)
  for (int i = 0; i < 4; i++)
    a[i].x += dx;
    //Вращение
    if (rotate) {
	  Point p = a[1];// указуем на центр вращения
	  for (int i = 0; i < 4; i++) {
		  int x = a[i].y - p.y;//y-y0
		  int y = a[i].x - p.x;//x-x0
		  a[i].x = p.x - x;
		  a[i].y = p.y + y;
	  }
	}

	//Движение тетрамина вниз 
	if (timer > delay) {
		for (int i = 0; i < 4; i++)
			a[i].y += 1;
		timer = 0;
	
	}


    int n = 3;//задаем тип тетрамино(3, 5, 4, 7)каждого отдельного кучочка
    //Первое поаявление
    if (a[0].x == 0)
	  //переведем "локальные" координаты кусочков  в "глобальные"
      for (int i = 0; i < 4; i++) {
		a[i].x = figures[n][i] % 2;//перемещение по горизонтале
		a[i].y = figures[n][i] / 2;//перемещение по вертикале
	  }
	dx = 0;
	rotate = 0;
 
   // Установка цвета фона - белый
  window.clear(Color::White);


  for (int i = 0; i < 4; i++) {
	  //Устанавливаем  позиции каждага кусочка тетрамино
	  sprite.setPosition(a[i].x * 18, a[i].y * 18);//18 - размер пиксилей

	  //отрисовка спрайта
	  window.draw(sprite);
  }
 

  // Отрисовка спрайта	 
  window.draw(sprite);

  // Отрисовка окна
  window.display();
}

return 0;
}



