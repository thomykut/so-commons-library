/*
 * Copyright (C) 2012 Sistemas Operativos - UTN FRBA. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef TEMPORAL_H_
#define TEMPORAL_H_

	#include <stdint.h>

	/**
	* @NAME: temporal_get_string_time
	* @DESC: Retorna un string con la hora actual,
	* con el formato recibido por parámetro.
	* Ejemplos:
	* temporal_get_string_time("%d/%m/%y") => "30/09/20"
	* temporal_get_string_time("%H:%M:%S:%MS") => "12:51:59:331"
	* temporal_get_string_time("%d/%m/%y %H:%M:%S") => "30/09/20 12:51:59"
	*/
	char *temporal_get_string_time(const char* format);

	/**
	* @NAME: t_state
	* @DESC: Estado de una variable temporal.
	*/
	typedef enum {
		STOPPED,
		RUNNING
	} t_state;

	/**
	* @NAME: t_temporal
	* @DESC: Estructura de una Variable temporal.
	*/
	typedef struct {
		struct timespec* current;
		int64_t elapsed_ms;
		t_state state;
	} t_temporal;

	/**
	* @NAME: temporal_create
	* @DESC: Crea una variable temporal.
	*/
	t_temporal* temporal_create(void);

	/**
	* @NAME: temporal_destroy
	* @DESC: Destruye una variable temporal.
	* @PARAMS: 
	*		temporal - Variable temporal a destruir.
	*/
	void temporal_destroy(t_temporal* temporal);

	/**
	* @NAME: temporal_gettime
	* @DESC: Retorna el tiempo transcurrido mientras el temporal estuvo activo en milisegundos.
	* @PARAMS:
	*		temporal - Variable temporal.
	*/
	int64_t temporal_gettime(t_temporal* temporal);
	
	/**
	* @NAME: temporal_gettime_since_running
	* @DESC: Retorna el tiempo transcurrido en el último período en el cual el temporal estuvo activo, en milisegundos.
			 si el temporal fue detenido y reanudado, sólo retornará el tiempo transcurrido desde el último reanudado.
			 Ejemplo:
			 	t_temporal temporal = temporal_create();
				sleep(2)
				temporal_stop(temporal);
				temporal_resume(temporal);
				sleep(1);
				temporal_gettime_since_running(temporal); => 1000 (Último período)
	* @PARAMS:
	*		temporal - Variable temporal.
	*/
	int64_t temporal_gettime_since_running(t_temporal* temporal);

	/**
	* @NAME: temporal_stop
	* @DESC: "Frena" el timer de una variable temporal. Deja de sumar tiempo.
	* @PARAMS:
	*		temporal - Variable temporal a frenar.
	*/
	void temporal_stop(t_temporal* temporal);

	/**
	* @NAME: temporal_resume
	* @DESC: Reanuda el timer de una variable temporal, vuelve a sumar tiempo.
	* @PARAMS:
	*		temporal - Variable temporal a reanudar.
	*/
	void temporal_resume(t_temporal* temporal);

	/**
	* @NAME: temporal_diff
	* @DESC: Retorna la diferencia entre dos variables temporales en milisegundos
	* @PARAMS:
	*		temporal_1 - Primer variable temporal, idealmente, la que se creó antes.
	*		temporal_2 - Segunda variable temporal.
	*/
	int64_t temporal_diff(t_temporal* start, t_temporal* end);
	
#endif /* TEMPORAL_H_ */
