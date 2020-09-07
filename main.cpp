#include <time.h>
#include <iostream>
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

//Проверка на выход за границы игрового поля
bool check() {
  for (int i = 0; i < 4; i++)
    if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)//не вышли ли мы за границы поля слева, справа и снизу
	  return 0;
	else if (field[a[i].y][a[i].x])//проверяем свобда ли ячейка или занята другим тетрамино
	  return 0;
  return 1;
}

int main() {
srand(time(0));
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
int colorNum = 1;//цвет
int n = rand() % 7;
bool beginGame = true; //bag

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

  //нажали на клавишу "виниз". Ускореное падение
  if (Keyboard::isKeyPressed(Keyboard::Down))
	  delay = 0.05;
  //Горизонт перемещение
  for (int i = 0; i < 4; i++) {
	  b[i] = a[i];
	  a[i].x += dx;
  }
  //Если вышли за пределы поля перемещения, возврат старых кординат
  if (!check()) {
    for (int i = 0; i  < 4; i++)
      a[i] = b[i];
  }

  //_____________Горизонтальное перемещение(сдвигаем все части)
  for (int i = 0; i < 4; i++) {
	b[i] = a[i];//Перемещаем координаты массива a[i] в b[i] 
    a[i].x += dx;//делаем "шаг влево" или "шаг вправо"
  }
  //Если вышли за пределы поля перемещения, возвращаем старые коордигаты
  if (!check()) {
    for (int i = 0; i < 4; i++)
      a[i] = b[i];// возвращаем старые координаты из вспомогательного массива b[]
  }

  //_____________Вращение
  if (rotate) {
	Point p = a[1];// указуем на центр вращения
	for (int i = 0; i < 4; i++) {
	  int x = a[i].y - p.y;//y-y0
	  int y = a[i].x - p.x;//x-x0
	  a[i].x = p.x - x;
	  a[i].y = p.y + y;
	 }
	 //Если вышли за пределы поля перемещения, возвращаем старые коордигаты
	if (!check()) {
	  for (int i = 0; i < 4; i++)
	    a[i] = b[i];// возвращаем старые координаты из вспомогательного массива b[]
	}
  }

  //__________________Движение тетрамина вниз 
  if (timer > delay) {
	for (int i = 0; i < 4; i++) {
	  b[i] = a[i];
	  a[i].y += 1;
	}
	if (!check()) {
	  for (int i = 0; i < 4; i++)
		field[b[i].y][b[i].x] = colorNum;//задаем тип цвета тетрамино
	  colorNum = 1 + rand() % 7;
	  int n = rand() % 7;
	  for (int i = 0; i < 4; i++) {
		  a[i].x = figures[n][i] % 2;
		  a[i].y = figures[n][i] / 2;
	  }
	}
     timer = 0;
  }
  /*
  //Уничтожение линии (проверка строки)
  int k = M - 1;
  for (int i = M - 1; i > 0; i--) {
	  int count = 0;
	  for (int j = 0; j < N; j--) {
		  if (field[i][j])//если есть элемент в строке
			  count++;//увеличуем счетчик на 1
		  field[k][j] = field[i][j];//вся строка заполнена элементами
	  }
	  if (count < N)
		  k--;
  }
  */
  //Первое появление тетрамино на поле?
  if (beginGame) {
    beginGame = false;
	n = rand() % 7;
	for (int i = 0; i < 4; i++) {
	  a[i].x = figures[n][i] % 2;
	  a[i].y = figures[n][i] / 2;
	}
  }
  
  
  dx = 0;
  rotate = 0;
  delay = 0.3;

  /*
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
   */

   // Установка цвета фона - белый
  window.clear(Color::White);
  for (int i = 0; i < M; i++ )
    for (int j = 0; j < N; j++) {
	  if (field[i][j] == 0)
	    continue;
	  //sprite.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
	  sprite.setPosition(j * 18, i * 18);
	  window.draw(sprite);
	}

  for (int i = 0; i < 4; i++) {
    //Устанавливаем  позиции каждага кусочка тетрамино
	sprite.setPosition(a[i].x * 18, a[i].y * 18);//18 - размер пиксилей

	//Устанавливаем позиуию каждого кусочка тетрамино
	//sprite.setPosition(a[i].x * 18, a[i].y * 18);

	//отрисовка спрайта
	window.draw(sprite);
  }
 
  

  /*
  //Уничтожение линии (заполненной строки)
  int k = M - 1;
  for (int i = M - 1; i > 0; i--) {
	  int count = 0;
	  for (int j = 0; j < N; j--) {
		  if (field[i][j])//если есть элемент в строке
			  count++;//увеличуем счетчик на 1
		  field[k][j] = field[i][j];//вся строка заполнена элементами
	  }
	  if (count < N)
		  k--;
  }
  */

  // Отрисовка спрайта	 
  window.draw(sprite);

  // Отрисовка окна
  window.display();
}

return 0;
}



