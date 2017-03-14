#ifndef RINGBUF_H
#define RINGBUF_H

#include <stdint.h>

/**
 * @brief Структура, описывающая кольцевой буффер.
 * 	Указатели begin и end бегают по
 * 	кругу между data и data_end.
 * 
 * 	begin  - указатель считываемого байта.
 * 	end - указатель записываемого байта
 * 
 * 	begin == end - буфер пуст
 * 
 * 	(end + 1) mod size == begin - буфер полон
 */
typedef struct {
	/**
	 * @brief Размер буфера, байт
	 */
	uint16_t	size;
	
	/**
	 * @brief Указатель на данные буфера
	 */
	uint8_t*	data;
	
	/**
	 * @brief Указатель на голову буфера
	 */
	uint8_t*	begin;
	
	/**
	 * @brief Указатель на хвост буфера
	 */
	uint8_t*	end;
	
	/**
	 * @brief Указатель на первый байт за хвостом (для сравнения)
	 */
	uint8_t*	data_end; // data+size
}tRingBuffer;

/**
 * @brief Инициализация кольцевого буфера
 * 
 * @param buf p_buf - указатель на описатель буфера
 * @param data p_data - указатель на данные 
 * @param size p_size - размер данных
 * 
 * Example:
 *	// Ring buffer init (0x200 bytes)
 * 	tRingBuffer	rb;
 * 	uint8_t		data[0x200];
 * 	ringBufferInit(&rb, data, sizeof(data));
 * 
 */
void ringBufferInit(tRingBuffer* buf, void* data, uint16_t size);

/**
 * @brief Записать в буфер данные data размером size
 * 
 * @param buf p_buf - указатель на описатель буфера
 * @param data p_data - указатель на записываемые данные 
 * @param size p_size - размер данных
 * 
 * @return uint16_t - сколько данные реально записано. 0 - ни одного байта, буфер полон.
 */
uint16_t ringBufferWrite(tRingBuffer* buf, void* data, uint16_t size);

/**
 * @brief Считать из буфера данные data размером size
 * 
 * @param buf p_buf - указатель на описатель буфера
 * @param data p_data - указатель на считываемые данные 
 * @param size p_size - размер данных
 * 
 * @return uint16_t - сколько данные реально считано. 0 - ни одного байта, буфер пуст.
 */
uint16_t ringBufferRead(tRingBuffer* buf, void* data, uint16_t size);

/**
 * @brief Вычисление размера буфера для хранения многобайтовых элементов.
 * 
 * Example:
 * 	
 * 	// Ring buffer init 0x400 elements, uint16_t type.
 * 	tRingBuffer	rb;
 * 	uint8_t		data[rbSize(0x400,sizeof(uint16_t))];
 * 	ringBufferInit(&rb, data, sizeof(data));
 * 
 */
#define rbSize(n, size) (n*size+1)

#endif // RINGBUF_H
