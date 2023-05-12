/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:15:28 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/12 12:35:46 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define FLAG_ID 0b00000001
#define FLAG_POS_VECTOR 0b00000010

#include <iostream>

struct Info{
	uint8_t flags;
	uint8_t size;
};