#ifndef READLINE_H
#define READLINE_H

/**
 * @brief Ввод строки размером size-1.
 * 	Окончание ввода - Enter.
 * 	Строка оканчивается на '\0'.
 * 	Возвращает - длину строки (без '\0').
 * 
 * @param buffer - буфер ввода
 * @param size - размер буфера ввода
 * @return int - количество введённых символов
 */
int readline(char* buffer, int size);


#endif /* READLINE_H */