from random import randint
import pygame
from typing import List, Tuple, Optional

# Константы для размеров поля и сетки:
SCREEN_WIDTH, SCREEN_HEIGHT = 640, 480
GRID_SIZE = 20
GRID_WIDTH = SCREEN_WIDTH // GRID_SIZE
GRID_HEIGHT = SCREEN_HEIGHT // GRID_SIZE

# Направления движения:
UP = (0, -1)
DOWN = (0, 1)
LEFT = (-1, 0)
RIGHT = (1, 0)

# Цвет фона - черный:
BOARD_BACKGROUND_COLOR = (0, 0, 0)

# Цвет границы ячейки
BORDER_COLOR = (93, 216, 228)

# Цвет яблока
APPLE_COLOR = (255, 0, 0)

# Цвет змейки
SNAKE_COLOR = (0, 255, 0)

# Скорость движения змейки:
SPEED = 10

# Настройка игрового окна:
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT), 0, 32)

# Заголовок окна игрового поля:
pygame.display.set_caption('Змейка')

# Настройка времени:
clock = pygame.time.Clock()


class GameObject:
   """
   Базовый класс для игровых объектов.
   """
   def __init__(self) -> None:
       self.position: Tuple[int, int] = (GRID_WIDTH // 2, GRID_HEIGHT // 2)
       self.body_color: Optional[Tuple[int, int, int]] = None

   def draw(self) -> None:
       """
       Метод для отрисовки игрового объекта.
       """
       pass


class Apple(GameObject):
   """
   Класс для работы с яблоком.
   """
   def __init__(self) -> None:
       """
       Инициализация объекта Apple.
       """
       super().__init__()
       self.body_color = APPLE_COLOR
       self.randomize_position()

   def randomize_position(self) -> None:
       """
       Метод для случайного размещения яблока на игровом поле.
       """
       self.position = (randint(0, GRID_WIDTH - 1), randint(0, GRID_HEIGHT - 1))

   def draw(self) -> None:
       """
       Метод для отрисовки яблока.
       """
       rect = pygame.Rect(
           (self.position[0] * GRID_SIZE, self.position[1] * GRID_SIZE),
           (GRID_SIZE, GRID_SIZE)
       )
       pygame.draw.rect(screen, self.body_color, rect)
       pygame.draw.rect(screen, BORDER_COLOR, rect, 1)


class Snake(GameObject):
   """
   Класс для работы со змейкой.
   """
   def __init__(self) -> None:
       """
       Инициализация объекта Snake.
       """
       super().__init__()
       self.length: int = 1
       self.positions: List[Tuple[int, int]] = [self.position]
       self.direction: Direction = RIGHT
       self.next_direction: Optional[Direction] = None
       self.body_color = SNAKE_COLOR
       self.last: Optional[Tuple[int, int]] = None
       self.growing: bool = False

   def get_head_position(self) -> Tuple[int, int]:
       """
       Метод для получения позиции головы змейки.
       :return: Позиция головы змейки.
       """
       return self.positions[0]

   def update_direction(self) -> None:
       """
       Метод для обновления направления движения змейки.
       """
       if self.next_direction:
           self.direction = self.next_direction
           self.next_direction = None

   def move(self) -> bool:
       """
       Метод для движения змейки.
       :return: True, если змейка не столкнулась с собой, иначе False.
       """
       head = self.get_head_position()
       x, y = self.direction
       new_position = ((head[0] + x) % GRID_WIDTH, (head[1] + y) % GRID_HEIGHT)
       
       if new_position in self.positions[1:]:
           self.reset()
           return False

       self.positions.insert(0, new_position)
       if not self.growing:
           self.last = self.positions.pop()
       else:
           self.length += 1
           self.growing = False
           self.last = None
       return True

   def grow(self) -> None:
       """
       Метод для увеличения длины змейки.
       """
       self.growing = True

   def reset(self) -> None:
       """
       Метод для сброса змейки в начальное состояние.
       """
       self.length = 1
       self.positions = [self.position]
       self.direction = RIGHT
       self.next_direction = None
       self.last = None
       self.growing = False

   def draw(self) -> None:
       """
       Метод для отрисовки змейки.
       """
       for position in self.positions:
           rect = pygame.Rect(
               (position[0] * GRID_SIZE, position[1] * GRID_SIZE),
               (GRID_SIZE, GRID_SIZE)
           )
           pygame.draw.rect(screen, self.body_color, rect)
           pygame.draw.rect(screen, BORDER_COLOR, rect, 1)


def handle_keys(game_object: Snake) -> None:
   """
   Метод для обработки нажатий клавиш.
   :param game_object: Объект Snake.
   """
   for event in pygame.event.get():
       if event.type == pygame.QUIT:
           pygame.quit()
           raise SystemExit
       elif event.type == pygame.KEYDOWN:
           if event.key == pygame.K_ESCAPE:
                pygame.quit()
                raise SystemExit
           if event.key == pygame.K_UP and game_object.direction != DOWN:
               game_object.next_direction = UP
           elif event.key == pygame.K_DOWN and game_object.direction != UP:
               game_object.next_direction = DOWN
           elif event.key == pygame.K_LEFT and game_object.direction != RIGHT:
               game_object.next_direction = LEFT
           elif event.key == pygame.K_RIGHT and game_object.direction != LEFT:
               game_object.next_direction = RIGHT


def main() -> None:
   """
   Главная функция игры.
   """
   pygame.init()
   snake = Snake()
   apple = Apple()

   while True:
       clock.tick(SPEED)
       handle_keys(snake)
       snake.update_direction()

       if not snake.move():
           apple.randomize_position()

       if snake.get_head_position() == apple.position:
           snake.grow()
           apple.randomize_position()
           while apple.position in snake.positions:
               apple.randomize_position()

       screen.fill(BOARD_BACKGROUND_COLOR)
       snake.draw()
       apple.draw()
       pygame.display.update()


if __name__ == '__main__':
   main()
