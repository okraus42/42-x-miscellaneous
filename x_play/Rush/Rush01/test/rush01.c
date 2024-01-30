/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:23:20 by okraus            #+#    #+#             */
/*   Updated: 2024/01/30 17:23:36 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#define SUCCESS 0
#define NO_SOLUTION 1
#define WRONG_INPUT 2
#define WRONG_NUMBER_OF_ARGUMENTS 3

// 		MATRIX
//		c1u c2u c3u c4u
// 	r1l	00  01  02  03	r1r
//
// 	r2l	10  11  12  13	r2r
//
// 	r3l	20  21  22  23	r3r
//
// 	r4l	30  31  32  33	r4r
//		c1d c2d c2d c4d

#define M33(a) (a & 0x3)
#define M32(a) ((a & 0xC) >> 2)
#define M31(a) ((a & 0x30) >> 4)
#define M30(a) ((a & 0xC0) >> 6)
#define M23(a) ((a & 0x300) >> 8)
#define M22(a) ((a & 0xC00) >> 10)
#define M21(a) ((a & 0x3000) >> 12)
#define M20(a) ((a & 0xC000) >> 14)
#define M13(a) ((a & 0x30000) >> 16)
#define M12(a) ((a & 0xC0000) >> 18)
#define M11(a) ((a & 0x300000) >> 20)
#define M10(a) ((a & 0xC00000) >> 22)
#define M03(a) ((a & 0x3000000) >> 24)
#define M02(a) ((a & 0xC000000) >> 26)
#define M01(a) ((a & 0x30000000) >> 28)
#define M00(a) ((a & 0xC0000000) >> 30)

#define BIG(a, b) (((b) > (a)) * 1)
#define BIGGER(a, b, c) ((((c) > (b)) && ((c) > (a))) * 1)
#define BIGGEST(a, b, c ,d) ((((d) > (c)) && ((d) > (b)) && ((d) > (a))) * 1)

#define VIS(a, b, c, d) (BIG(a, b) + BIGGER(a, b, c) + BIGGEST(a, b, c, d))

#define C1U(a) (VIS(M00(a), M10(a), M20(a), M30(a)))
#define C2U(a) (VIS(M01(a), M11(a), M21(a), M31(a)))
#define C3U(a) (VIS(M02(a), M12(a), M22(a), M32(a)))
#define C4U(a) (VIS(M03(a), M13(a), M23(a), M33(a)))
#define C1D(a) (VIS(M30(a), M20(a), M10(a), M00(a)))
#define C2D(a) (VIS(M31(a), M21(a), M11(a), M01(a)))
#define C3D(a) (VIS(M32(a), M22(a), M12(a), M02(a)))
#define C4D(a) (VIS(M33(a), M23(a), M13(a), M03(a)))
#define C1L(a) (VIS(M00(a), M01(a), M02(a), M03(a)))
#define C2L(a) (VIS(M10(a), M11(a), M12(a), M13(a)))
#define C3L(a) (VIS(M20(a), M21(a), M22(a), M23(a)))
#define C4L(a) (VIS(M30(a), M31(a), M32(a), M33(a)))
#define C1R(a) (VIS(M03(a), M02(a), M01(a), M00(a)))
#define C2R(a) (VIS(M13(a), M12(a), M11(a), M10(a)))
#define C3R(a) (VIS(M23(a), M22(a), M21(a), M20(a)))
#define C4R(a) (VIS(M33(a), M32(a), M31(a), M30(a)))

const unsigned char	solutions[576][33] = {
	"1 2 3 4\n2 1 4 3\n3 4 1 2\n4 3 2 1\n",
	"1 2 3 4\n2 1 4 3\n3 4 2 1\n4 3 1 2\n",
	"1 2 3 4\n2 1 4 3\n4 3 1 2\n3 4 2 1\n",
	"1 2 3 4\n2 1 4 3\n4 3 2 1\n3 4 1 2\n",
	"1 2 3 4\n2 3 4 1\n3 4 1 2\n4 1 2 3\n",
	"1 2 3 4\n2 3 4 1\n4 1 2 3\n3 4 1 2\n",
	"1 2 3 4\n2 4 1 3\n3 1 4 2\n4 3 2 1\n",
	"1 2 3 4\n2 4 1 3\n4 3 2 1\n3 1 4 2\n",
	"1 2 3 4\n3 1 4 2\n2 4 1 3\n4 3 2 1\n",
	"1 2 3 4\n3 1 4 2\n4 3 2 1\n2 4 1 3\n",
	"1 2 3 4\n3 4 1 2\n2 1 4 3\n4 3 2 1\n",
	"1 2 3 4\n3 4 1 2\n2 3 4 1\n4 1 2 3\n",
	"1 2 3 4\n3 4 1 2\n4 1 2 3\n2 3 4 1\n",
	"1 2 3 4\n3 4 1 2\n4 3 2 1\n2 1 4 3\n",
	"1 2 3 4\n3 4 2 1\n2 1 4 3\n4 3 1 2\n",
	"1 2 3 4\n3 4 2 1\n4 3 1 2\n2 1 4 3\n",
	"1 2 3 4\n4 1 2 3\n2 3 4 1\n3 4 1 2\n",
	"1 2 3 4\n4 1 2 3\n3 4 1 2\n2 3 4 1\n",
	"1 2 3 4\n4 3 1 2\n2 1 4 3\n3 4 2 1\n",
	"1 2 3 4\n4 3 1 2\n3 4 2 1\n2 1 4 3\n",
	"1 2 3 4\n4 3 2 1\n2 1 4 3\n3 4 1 2\n",
	"1 2 3 4\n4 3 2 1\n2 4 1 3\n3 1 4 2\n",
	"1 2 3 4\n4 3 2 1\n3 1 4 2\n2 4 1 3\n",
	"1 2 3 4\n4 3 2 1\n3 4 1 2\n2 1 4 3\n",
	"1 2 4 3\n2 1 3 4\n3 4 1 2\n4 3 2 1\n",
	"1 2 4 3\n2 1 3 4\n3 4 2 1\n4 3 1 2\n",
	"1 2 4 3\n2 1 3 4\n4 3 1 2\n3 4 2 1\n",
	"1 2 4 3\n2 1 3 4\n4 3 2 1\n3 4 1 2\n",
	"1 2 4 3\n2 3 1 4\n3 4 2 1\n4 1 3 2\n",
	"1 2 4 3\n2 3 1 4\n4 1 3 2\n3 4 2 1\n",
	"1 2 4 3\n2 4 3 1\n3 1 2 4\n4 3 1 2\n",
	"1 2 4 3\n2 4 3 1\n4 3 1 2\n3 1 2 4\n",
	"1 2 4 3\n3 1 2 4\n2 4 3 1\n4 3 1 2\n",
	"1 2 4 3\n3 1 2 4\n4 3 1 2\n2 4 3 1\n",
	"1 2 4 3\n3 4 1 2\n2 1 3 4\n4 3 2 1\n",
	"1 2 4 3\n3 4 1 2\n4 3 2 1\n2 1 3 4\n",
	"1 2 4 3\n3 4 2 1\n2 1 3 4\n4 3 1 2\n",
	"1 2 4 3\n3 4 2 1\n2 3 1 4\n4 1 3 2\n",
	"1 2 4 3\n3 4 2 1\n4 1 3 2\n2 3 1 4\n",
	"1 2 4 3\n3 4 2 1\n4 3 1 2\n2 1 3 4\n",
	"1 2 4 3\n4 1 3 2\n2 3 1 4\n3 4 2 1\n",
	"1 2 4 3\n4 1 3 2\n3 4 2 1\n2 3 1 4\n",
	"1 2 4 3\n4 3 1 2\n2 1 3 4\n3 4 2 1\n",
	"1 2 4 3\n4 3 1 2\n2 4 3 1\n3 1 2 4\n",
	"1 2 4 3\n4 3 1 2\n3 1 2 4\n2 4 3 1\n",
	"1 2 4 3\n4 3 1 2\n3 4 2 1\n2 1 3 4\n",
	"1 2 4 3\n4 3 2 1\n2 1 3 4\n3 4 1 2\n",
	"1 2 4 3\n4 3 2 1\n3 4 1 2\n2 1 3 4\n",
	"1 3 2 4\n2 1 4 3\n3 4 1 2\n4 2 3 1\n",
	"1 3 2 4\n2 1 4 3\n4 2 3 1\n3 4 1 2\n",
	"1 3 2 4\n2 4 1 3\n3 1 4 2\n4 2 3 1\n",
	"1 3 2 4\n2 4 1 3\n3 2 4 1\n4 1 3 2\n",
	"1 3 2 4\n2 4 1 3\n4 1 3 2\n3 2 4 1\n",
	"1 3 2 4\n2 4 1 3\n4 2 3 1\n3 1 4 2\n",
	"1 3 2 4\n2 4 3 1\n3 1 4 2\n4 2 1 3\n",
	"1 3 2 4\n2 4 3 1\n4 2 1 3\n3 1 4 2\n",
	"1 3 2 4\n3 1 4 2\n2 4 1 3\n4 2 3 1\n",
	"1 3 2 4\n3 1 4 2\n2 4 3 1\n4 2 1 3\n",
	"1 3 2 4\n3 1 4 2\n4 2 1 3\n2 4 3 1\n",
	"1 3 2 4\n3 1 4 2\n4 2 3 1\n2 4 1 3\n",
	"1 3 2 4\n3 2 4 1\n2 4 1 3\n4 1 3 2\n",
	"1 3 2 4\n3 2 4 1\n4 1 3 2\n2 4 1 3\n",
	"1 3 2 4\n3 4 1 2\n2 1 4 3\n4 2 3 1\n",
	"1 3 2 4\n3 4 1 2\n4 2 3 1\n2 1 4 3\n",
	"1 3 2 4\n4 1 3 2\n2 4 1 3\n3 2 4 1\n",
	"1 3 2 4\n4 1 3 2\n3 2 4 1\n2 4 1 3\n",
	"1 3 2 4\n4 2 1 3\n2 4 3 1\n3 1 4 2\n",
	"1 3 2 4\n4 2 1 3\n3 1 4 2\n2 4 3 1\n",
	"1 3 2 4\n4 2 3 1\n2 1 4 3\n3 4 1 2\n",
	"1 3 2 4\n4 2 3 1\n2 4 1 3\n3 1 4 2\n",
	"1 3 2 4\n4 2 3 1\n3 1 4 2\n2 4 1 3\n",
	"1 3 2 4\n4 2 3 1\n3 4 1 2\n2 1 4 3\n",
	"1 3 4 2\n2 1 3 4\n3 4 2 1\n4 2 1 3\n",
	"1 3 4 2\n2 1 3 4\n4 2 1 3\n3 4 2 1\n",
	"1 3 4 2\n2 4 1 3\n3 1 2 4\n4 2 3 1\n",
	"1 3 4 2\n2 4 1 3\n4 2 3 1\n3 1 2 4\n",
	"1 3 4 2\n2 4 3 1\n3 1 2 4\n4 2 1 3\n",
	"1 3 4 2\n2 4 3 1\n3 2 1 4\n4 1 2 3\n",
	"1 3 4 2\n2 4 3 1\n4 1 2 3\n3 2 1 4\n",
	"1 3 4 2\n2 4 3 1\n4 2 1 3\n3 1 2 4\n",
	"1 3 4 2\n3 1 2 4\n2 4 1 3\n4 2 3 1\n",
	"1 3 4 2\n3 1 2 4\n2 4 3 1\n4 2 1 3\n",
	"1 3 4 2\n3 1 2 4\n4 2 1 3\n2 4 3 1\n",
	"1 3 4 2\n3 1 2 4\n4 2 3 1\n2 4 1 3\n",
	"1 3 4 2\n3 2 1 4\n2 4 3 1\n4 1 2 3\n",
	"1 3 4 2\n3 2 1 4\n4 1 2 3\n2 4 3 1\n",
	"1 3 4 2\n3 4 2 1\n2 1 3 4\n4 2 1 3\n",
	"1 3 4 2\n3 4 2 1\n4 2 1 3\n2 1 3 4\n",
	"1 3 4 2\n4 1 2 3\n2 4 3 1\n3 2 1 4\n",
	"1 3 4 2\n4 1 2 3\n3 2 1 4\n2 4 3 1\n",
	"1 3 4 2\n4 2 1 3\n2 1 3 4\n3 4 2 1\n",
	"1 3 4 2\n4 2 1 3\n2 4 3 1\n3 1 2 4\n",
	"1 3 4 2\n4 2 1 3\n3 1 2 4\n2 4 3 1\n",
	"1 3 4 2\n4 2 1 3\n3 4 2 1\n2 1 3 4\n",
	"1 3 4 2\n4 2 3 1\n2 4 1 3\n3 1 2 4\n",
	"1 3 4 2\n4 2 3 1\n3 1 2 4\n2 4 1 3\n",
	"1 4 2 3\n2 1 3 4\n3 2 4 1\n4 3 1 2\n",
	"1 4 2 3\n2 1 3 4\n4 3 1 2\n3 2 4 1\n",
	"1 4 2 3\n2 3 1 4\n3 1 4 2\n4 2 3 1\n",
	"1 4 2 3\n2 3 1 4\n3 2 4 1\n4 1 3 2\n",
	"1 4 2 3\n2 3 1 4\n4 1 3 2\n3 2 4 1\n",
	"1 4 2 3\n2 3 1 4\n4 2 3 1\n3 1 4 2\n",
	"1 4 2 3\n2 3 4 1\n3 2 1 4\n4 1 3 2\n",
	"1 4 2 3\n2 3 4 1\n4 1 3 2\n3 2 1 4\n",
	"1 4 2 3\n3 1 4 2\n2 3 1 4\n4 2 3 1\n",
	"1 4 2 3\n3 1 4 2\n4 2 3 1\n2 3 1 4\n",
	"1 4 2 3\n3 2 1 4\n2 3 4 1\n4 1 3 2\n",
	"1 4 2 3\n3 2 1 4\n4 1 3 2\n2 3 4 1\n",
	"1 4 2 3\n3 2 4 1\n2 1 3 4\n4 3 1 2\n",
	"1 4 2 3\n3 2 4 1\n2 3 1 4\n4 1 3 2\n",
	"1 4 2 3\n3 2 4 1\n4 1 3 2\n2 3 1 4\n",
	"1 4 2 3\n3 2 4 1\n4 3 1 2\n2 1 3 4\n",
	"1 4 2 3\n4 1 3 2\n2 3 1 4\n3 2 4 1\n",
	"1 4 2 3\n4 1 3 2\n2 3 4 1\n3 2 1 4\n",
	"1 4 2 3\n4 1 3 2\n3 2 1 4\n2 3 4 1\n",
	"1 4 2 3\n4 1 3 2\n3 2 4 1\n2 3 1 4\n",
	"1 4 2 3\n4 2 3 1\n2 3 1 4\n3 1 4 2\n",
	"1 4 2 3\n4 2 3 1\n3 1 4 2\n2 3 1 4\n",
	"1 4 2 3\n4 3 1 2\n2 1 3 4\n3 2 4 1\n",
	"1 4 2 3\n4 3 1 2\n3 2 4 1\n2 1 3 4\n",
	"1 4 3 2\n2 1 4 3\n3 2 1 4\n4 3 2 1\n",
	"1 4 3 2\n2 1 4 3\n4 3 2 1\n3 2 1 4\n",
	"1 4 3 2\n2 3 1 4\n3 2 4 1\n4 1 2 3\n",
	"1 4 3 2\n2 3 1 4\n4 1 2 3\n3 2 4 1\n",
	"1 4 3 2\n2 3 4 1\n3 1 2 4\n4 2 1 3\n",
	"1 4 3 2\n2 3 4 1\n3 2 1 4\n4 1 2 3\n",
	"1 4 3 2\n2 3 4 1\n4 1 2 3\n3 2 1 4\n",
	"1 4 3 2\n2 3 4 1\n4 2 1 3\n3 1 2 4\n",
	"1 4 3 2\n3 1 2 4\n2 3 4 1\n4 2 1 3\n",
	"1 4 3 2\n3 1 2 4\n4 2 1 3\n2 3 4 1\n",
	"1 4 3 2\n3 2 1 4\n2 1 4 3\n4 3 2 1\n",
	"1 4 3 2\n3 2 1 4\n2 3 4 1\n4 1 2 3\n",
	"1 4 3 2\n3 2 1 4\n4 1 2 3\n2 3 4 1\n",
	"1 4 3 2\n3 2 1 4\n4 3 2 1\n2 1 4 3\n",
	"1 4 3 2\n3 2 4 1\n2 3 1 4\n4 1 2 3\n",
	"1 4 3 2\n3 2 4 1\n4 1 2 3\n2 3 1 4\n",
	"1 4 3 2\n4 1 2 3\n2 3 1 4\n3 2 4 1\n",
	"1 4 3 2\n4 1 2 3\n2 3 4 1\n3 2 1 4\n",
	"1 4 3 2\n4 1 2 3\n3 2 1 4\n2 3 4 1\n",
	"1 4 3 2\n4 1 2 3\n3 2 4 1\n2 3 1 4\n",
	"1 4 3 2\n4 2 1 3\n2 3 4 1\n3 1 2 4\n",
	"1 4 3 2\n4 2 1 3\n3 1 2 4\n2 3 4 1\n",
	"1 4 3 2\n4 3 2 1\n2 1 4 3\n3 2 1 4\n",
	"1 4 3 2\n4 3 2 1\n3 2 1 4\n2 1 4 3\n",
	"2 1 3 4\n1 2 4 3\n3 4 1 2\n4 3 2 1\n",
	"2 1 3 4\n1 2 4 3\n3 4 2 1\n4 3 1 2\n",
	"2 1 3 4\n1 2 4 3\n4 3 1 2\n3 4 2 1\n",
	"2 1 3 4\n1 2 4 3\n4 3 2 1\n3 4 1 2\n",
	"2 1 3 4\n1 3 4 2\n3 4 2 1\n4 2 1 3\n",
	"2 1 3 4\n1 3 4 2\n4 2 1 3\n3 4 2 1\n",
	"2 1 3 4\n1 4 2 3\n3 2 4 1\n4 3 1 2\n",
	"2 1 3 4\n1 4 2 3\n4 3 1 2\n3 2 4 1\n",
	"2 1 3 4\n3 2 4 1\n1 4 2 3\n4 3 1 2\n",
	"2 1 3 4\n3 2 4 1\n4 3 1 2\n1 4 2 3\n",
	"2 1 3 4\n3 4 1 2\n1 2 4 3\n4 3 2 1\n",
	"2 1 3 4\n3 4 1 2\n4 3 2 1\n1 2 4 3\n",
	"2 1 3 4\n3 4 2 1\n1 2 4 3\n4 3 1 2\n",
	"2 1 3 4\n3 4 2 1\n1 3 4 2\n4 2 1 3\n",
	"2 1 3 4\n3 4 2 1\n4 2 1 3\n1 3 4 2\n",
	"2 1 3 4\n3 4 2 1\n4 3 1 2\n1 2 4 3\n",
	"2 1 3 4\n4 2 1 3\n1 3 4 2\n3 4 2 1\n",
	"2 1 3 4\n4 2 1 3\n3 4 2 1\n1 3 4 2\n",
	"2 1 3 4\n4 3 1 2\n1 2 4 3\n3 4 2 1\n",
	"2 1 3 4\n4 3 1 2\n1 4 2 3\n3 2 4 1\n",
	"2 1 3 4\n4 3 1 2\n3 2 4 1\n1 4 2 3\n",
	"2 1 3 4\n4 3 1 2\n3 4 2 1\n1 2 4 3\n",
	"2 1 3 4\n4 3 2 1\n1 2 4 3\n3 4 1 2\n",
	"2 1 3 4\n4 3 2 1\n3 4 1 2\n1 2 4 3\n",
	"2 1 4 3\n1 2 3 4\n3 4 1 2\n4 3 2 1\n",
	"2 1 4 3\n1 2 3 4\n3 4 2 1\n4 3 1 2\n",
	"2 1 4 3\n1 2 3 4\n4 3 1 2\n3 4 2 1\n",
	"2 1 4 3\n1 2 3 4\n4 3 2 1\n3 4 1 2\n",
	"2 1 4 3\n1 3 2 4\n3 4 1 2\n4 2 3 1\n",
	"2 1 4 3\n1 3 2 4\n4 2 3 1\n3 4 1 2\n",
	"2 1 4 3\n1 4 3 2\n3 2 1 4\n4 3 2 1\n",
	"2 1 4 3\n1 4 3 2\n4 3 2 1\n3 2 1 4\n",
	"2 1 4 3\n3 2 1 4\n1 4 3 2\n4 3 2 1\n",
	"2 1 4 3\n3 2 1 4\n4 3 2 1\n1 4 3 2\n",
	"2 1 4 3\n3 4 1 2\n1 2 3 4\n4 3 2 1\n",
	"2 1 4 3\n3 4 1 2\n1 3 2 4\n4 2 3 1\n",
	"2 1 4 3\n3 4 1 2\n4 2 3 1\n1 3 2 4\n",
	"2 1 4 3\n3 4 1 2\n4 3 2 1\n1 2 3 4\n",
	"2 1 4 3\n3 4 2 1\n1 2 3 4\n4 3 1 2\n",
	"2 1 4 3\n3 4 2 1\n4 3 1 2\n1 2 3 4\n",
	"2 1 4 3\n4 2 3 1\n1 3 2 4\n3 4 1 2\n",
	"2 1 4 3\n4 2 3 1\n3 4 1 2\n1 3 2 4\n",
	"2 1 4 3\n4 3 1 2\n1 2 3 4\n3 4 2 1\n",
	"2 1 4 3\n4 3 1 2\n3 4 2 1\n1 2 3 4\n",
	"2 1 4 3\n4 3 2 1\n1 2 3 4\n3 4 1 2\n",
	"2 1 4 3\n4 3 2 1\n1 4 3 2\n3 2 1 4\n",
	"2 1 4 3\n4 3 2 1\n3 2 1 4\n1 4 3 2\n",
	"2 1 4 3\n4 3 2 1\n3 4 1 2\n1 2 3 4\n",
	"2 3 1 4\n1 2 4 3\n3 4 2 1\n4 1 3 2\n",
	"2 3 1 4\n1 2 4 3\n4 1 3 2\n3 4 2 1\n",
	"2 3 1 4\n1 4 2 3\n3 1 4 2\n4 2 3 1\n",
	"2 3 1 4\n1 4 2 3\n3 2 4 1\n4 1 3 2\n",
	"2 3 1 4\n1 4 2 3\n4 1 3 2\n3 2 4 1\n",
	"2 3 1 4\n1 4 2 3\n4 2 3 1\n3 1 4 2\n",
	"2 3 1 4\n1 4 3 2\n3 2 4 1\n4 1 2 3\n",
	"2 3 1 4\n1 4 3 2\n4 1 2 3\n3 2 4 1\n",
	"2 3 1 4\n3 1 4 2\n1 4 2 3\n4 2 3 1\n",
	"2 3 1 4\n3 1 4 2\n4 2 3 1\n1 4 2 3\n",
	"2 3 1 4\n3 2 4 1\n1 4 2 3\n4 1 3 2\n",
	"2 3 1 4\n3 2 4 1\n1 4 3 2\n4 1 2 3\n",
	"2 3 1 4\n3 2 4 1\n4 1 2 3\n1 4 3 2\n",
	"2 3 1 4\n3 2 4 1\n4 1 3 2\n1 4 2 3\n",
	"2 3 1 4\n3 4 2 1\n1 2 4 3\n4 1 3 2\n",
	"2 3 1 4\n3 4 2 1\n4 1 3 2\n1 2 4 3\n",
	"2 3 1 4\n4 1 2 3\n1 4 3 2\n3 2 4 1\n",
	"2 3 1 4\n4 1 2 3\n3 2 4 1\n1 4 3 2\n",
	"2 3 1 4\n4 1 3 2\n1 2 4 3\n3 4 2 1\n",
	"2 3 1 4\n4 1 3 2\n1 4 2 3\n3 2 4 1\n",
	"2 3 1 4\n4 1 3 2\n3 2 4 1\n1 4 2 3\n",
	"2 3 1 4\n4 1 3 2\n3 4 2 1\n1 2 4 3\n",
	"2 3 1 4\n4 2 3 1\n1 4 2 3\n3 1 4 2\n",
	"2 3 1 4\n4 2 3 1\n3 1 4 2\n1 4 2 3\n",
	"2 3 4 1\n1 2 3 4\n3 4 1 2\n4 1 2 3\n",
	"2 3 4 1\n1 2 3 4\n4 1 2 3\n3 4 1 2\n",
	"2 3 4 1\n1 4 2 3\n3 2 1 4\n4 1 3 2\n",
	"2 3 4 1\n1 4 2 3\n4 1 3 2\n3 2 1 4\n",
	"2 3 4 1\n1 4 3 2\n3 1 2 4\n4 2 1 3\n",
	"2 3 4 1\n1 4 3 2\n3 2 1 4\n4 1 2 3\n",
	"2 3 4 1\n1 4 3 2\n4 1 2 3\n3 2 1 4\n",
	"2 3 4 1\n1 4 3 2\n4 2 1 3\n3 1 2 4\n",
	"2 3 4 1\n3 1 2 4\n1 4 3 2\n4 2 1 3\n",
	"2 3 4 1\n3 1 2 4\n4 2 1 3\n1 4 3 2\n",
	"2 3 4 1\n3 2 1 4\n1 4 2 3\n4 1 3 2\n",
	"2 3 4 1\n3 2 1 4\n1 4 3 2\n4 1 2 3\n",
	"2 3 4 1\n3 2 1 4\n4 1 2 3\n1 4 3 2\n",
	"2 3 4 1\n3 2 1 4\n4 1 3 2\n1 4 2 3\n",
	"2 3 4 1\n3 4 1 2\n1 2 3 4\n4 1 2 3\n",
	"2 3 4 1\n3 4 1 2\n4 1 2 3\n1 2 3 4\n",
	"2 3 4 1\n4 1 2 3\n1 2 3 4\n3 4 1 2\n",
	"2 3 4 1\n4 1 2 3\n1 4 3 2\n3 2 1 4\n",
	"2 3 4 1\n4 1 2 3\n3 2 1 4\n1 4 3 2\n",
	"2 3 4 1\n4 1 2 3\n3 4 1 2\n1 2 3 4\n",
	"2 3 4 1\n4 1 3 2\n1 4 2 3\n3 2 1 4\n",
	"2 3 4 1\n4 1 3 2\n3 2 1 4\n1 4 2 3\n",
	"2 3 4 1\n4 2 1 3\n1 4 3 2\n3 1 2 4\n",
	"2 3 4 1\n4 2 1 3\n3 1 2 4\n1 4 3 2\n",
	"2 4 1 3\n1 2 3 4\n3 1 4 2\n4 3 2 1\n",
	"2 4 1 3\n1 2 3 4\n4 3 2 1\n3 1 4 2\n",
	"2 4 1 3\n1 3 2 4\n3 1 4 2\n4 2 3 1\n",
	"2 4 1 3\n1 3 2 4\n3 2 4 1\n4 1 3 2\n",
	"2 4 1 3\n1 3 2 4\n4 1 3 2\n3 2 4 1\n",
	"2 4 1 3\n1 3 2 4\n4 2 3 1\n3 1 4 2\n",
	"2 4 1 3\n1 3 4 2\n3 1 2 4\n4 2 3 1\n",
	"2 4 1 3\n1 3 4 2\n4 2 3 1\n3 1 2 4\n",
	"2 4 1 3\n3 1 2 4\n1 3 4 2\n4 2 3 1\n",
	"2 4 1 3\n3 1 2 4\n4 2 3 1\n1 3 4 2\n",
	"2 4 1 3\n3 1 4 2\n1 2 3 4\n4 3 2 1\n",
	"2 4 1 3\n3 1 4 2\n1 3 2 4\n4 2 3 1\n",
	"2 4 1 3\n3 1 4 2\n4 2 3 1\n1 3 2 4\n",
	"2 4 1 3\n3 1 4 2\n4 3 2 1\n1 2 3 4\n",
	"2 4 1 3\n3 2 4 1\n1 3 2 4\n4 1 3 2\n",
	"2 4 1 3\n3 2 4 1\n4 1 3 2\n1 3 2 4\n",
	"2 4 1 3\n4 1 3 2\n1 3 2 4\n3 2 4 1\n",
	"2 4 1 3\n4 1 3 2\n3 2 4 1\n1 3 2 4\n",
	"2 4 1 3\n4 2 3 1\n1 3 2 4\n3 1 4 2\n",
	"2 4 1 3\n4 2 3 1\n1 3 4 2\n3 1 2 4\n",
	"2 4 1 3\n4 2 3 1\n3 1 2 4\n1 3 4 2\n",
	"2 4 1 3\n4 2 3 1\n3 1 4 2\n1 3 2 4\n",
	"2 4 1 3\n4 3 2 1\n1 2 3 4\n3 1 4 2\n",
	"2 4 1 3\n4 3 2 1\n3 1 4 2\n1 2 3 4\n",
	"2 4 3 1\n1 2 4 3\n3 1 2 4\n4 3 1 2\n",
	"2 4 3 1\n1 2 4 3\n4 3 1 2\n3 1 2 4\n",
	"2 4 3 1\n1 3 2 4\n3 1 4 2\n4 2 1 3\n",
	"2 4 3 1\n1 3 2 4\n4 2 1 3\n3 1 4 2\n",
	"2 4 3 1\n1 3 4 2\n3 1 2 4\n4 2 1 3\n",
	"2 4 3 1\n1 3 4 2\n3 2 1 4\n4 1 2 3\n",
	"2 4 3 1\n1 3 4 2\n4 1 2 3\n3 2 1 4\n",
	"2 4 3 1\n1 3 4 2\n4 2 1 3\n3 1 2 4\n",
	"2 4 3 1\n3 1 2 4\n1 2 4 3\n4 3 1 2\n",
	"2 4 3 1\n3 1 2 4\n1 3 4 2\n4 2 1 3\n",
	"2 4 3 1\n3 1 2 4\n4 2 1 3\n1 3 4 2\n",
	"2 4 3 1\n3 1 2 4\n4 3 1 2\n1 2 4 3\n",
	"2 4 3 1\n3 1 4 2\n1 3 2 4\n4 2 1 3\n",
	"2 4 3 1\n3 1 4 2\n4 2 1 3\n1 3 2 4\n",
	"2 4 3 1\n3 2 1 4\n1 3 4 2\n4 1 2 3\n",
	"2 4 3 1\n3 2 1 4\n4 1 2 3\n1 3 4 2\n",
	"2 4 3 1\n4 1 2 3\n1 3 4 2\n3 2 1 4\n",
	"2 4 3 1\n4 1 2 3\n3 2 1 4\n1 3 4 2\n",
	"2 4 3 1\n4 2 1 3\n1 3 2 4\n3 1 4 2\n",
	"2 4 3 1\n4 2 1 3\n1 3 4 2\n3 1 2 4\n",
	"2 4 3 1\n4 2 1 3\n3 1 2 4\n1 3 4 2\n",
	"2 4 3 1\n4 2 1 3\n3 1 4 2\n1 3 2 4\n",
	"2 4 3 1\n4 3 1 2\n1 2 4 3\n3 1 2 4\n",
	"2 4 3 1\n4 3 1 2\n3 1 2 4\n1 2 4 3\n",
	"3 1 2 4\n1 2 4 3\n2 4 3 1\n4 3 1 2\n",
	"3 1 2 4\n1 2 4 3\n4 3 1 2\n2 4 3 1\n",
	"3 1 2 4\n1 3 4 2\n2 4 1 3\n4 2 3 1\n",
	"3 1 2 4\n1 3 4 2\n2 4 3 1\n4 2 1 3\n",
	"3 1 2 4\n1 3 4 2\n4 2 1 3\n2 4 3 1\n",
	"3 1 2 4\n1 3 4 2\n4 2 3 1\n2 4 1 3\n",
	"3 1 2 4\n1 4 3 2\n2 3 4 1\n4 2 1 3\n",
	"3 1 2 4\n1 4 3 2\n4 2 1 3\n2 3 4 1\n",
	"3 1 2 4\n2 3 4 1\n1 4 3 2\n4 2 1 3\n",
	"3 1 2 4\n2 3 4 1\n4 2 1 3\n1 4 3 2\n",
	"3 1 2 4\n2 4 1 3\n1 3 4 2\n4 2 3 1\n",
	"3 1 2 4\n2 4 1 3\n4 2 3 1\n1 3 4 2\n",
	"3 1 2 4\n2 4 3 1\n1 2 4 3\n4 3 1 2\n",
	"3 1 2 4\n2 4 3 1\n1 3 4 2\n4 2 1 3\n",
	"3 1 2 4\n2 4 3 1\n4 2 1 3\n1 3 4 2\n",
	"3 1 2 4\n2 4 3 1\n4 3 1 2\n1 2 4 3\n",
	"3 1 2 4\n4 2 1 3\n1 3 4 2\n2 4 3 1\n",
	"3 1 2 4\n4 2 1 3\n1 4 3 2\n2 3 4 1\n",
	"3 1 2 4\n4 2 1 3\n2 3 4 1\n1 4 3 2\n",
	"3 1 2 4\n4 2 1 3\n2 4 3 1\n1 3 4 2\n",
	"3 1 2 4\n4 2 3 1\n1 3 4 2\n2 4 1 3\n",
	"3 1 2 4\n4 2 3 1\n2 4 1 3\n1 3 4 2\n",
	"3 1 2 4\n4 3 1 2\n1 2 4 3\n2 4 3 1\n",
	"3 1 2 4\n4 3 1 2\n2 4 3 1\n1 2 4 3\n",
	"3 1 4 2\n1 2 3 4\n2 4 1 3\n4 3 2 1\n",
	"3 1 4 2\n1 2 3 4\n4 3 2 1\n2 4 1 3\n",
	"3 1 4 2\n1 3 2 4\n2 4 1 3\n4 2 3 1\n",
	"3 1 4 2\n1 3 2 4\n2 4 3 1\n4 2 1 3\n",
	"3 1 4 2\n1 3 2 4\n4 2 1 3\n2 4 3 1\n",
	"3 1 4 2\n1 3 2 4\n4 2 3 1\n2 4 1 3\n",
	"3 1 4 2\n1 4 2 3\n2 3 1 4\n4 2 3 1\n",
	"3 1 4 2\n1 4 2 3\n4 2 3 1\n2 3 1 4\n",
	"3 1 4 2\n2 3 1 4\n1 4 2 3\n4 2 3 1\n",
	"3 1 4 2\n2 3 1 4\n4 2 3 1\n1 4 2 3\n",
	"3 1 4 2\n2 4 1 3\n1 2 3 4\n4 3 2 1\n",
	"3 1 4 2\n2 4 1 3\n1 3 2 4\n4 2 3 1\n",
	"3 1 4 2\n2 4 1 3\n4 2 3 1\n1 3 2 4\n",
	"3 1 4 2\n2 4 1 3\n4 3 2 1\n1 2 3 4\n",
	"3 1 4 2\n2 4 3 1\n1 3 2 4\n4 2 1 3\n",
	"3 1 4 2\n2 4 3 1\n4 2 1 3\n1 3 2 4\n",
	"3 1 4 2\n4 2 1 3\n1 3 2 4\n2 4 3 1\n",
	"3 1 4 2\n4 2 1 3\n2 4 3 1\n1 3 2 4\n",
	"3 1 4 2\n4 2 3 1\n1 3 2 4\n2 4 1 3\n",
	"3 1 4 2\n4 2 3 1\n1 4 2 3\n2 3 1 4\n",
	"3 1 4 2\n4 2 3 1\n2 3 1 4\n1 4 2 3\n",
	"3 1 4 2\n4 2 3 1\n2 4 1 3\n1 3 2 4\n",
	"3 1 4 2\n4 3 2 1\n1 2 3 4\n2 4 1 3\n",
	"3 1 4 2\n4 3 2 1\n2 4 1 3\n1 2 3 4\n",
	"3 2 1 4\n1 3 4 2\n2 4 3 1\n4 1 2 3\n",
	"3 2 1 4\n1 3 4 2\n4 1 2 3\n2 4 3 1\n",
	"3 2 1 4\n1 4 2 3\n2 3 4 1\n4 1 3 2\n",
	"3 2 1 4\n1 4 2 3\n4 1 3 2\n2 3 4 1\n",
	"3 2 1 4\n1 4 3 2\n2 1 4 3\n4 3 2 1\n",
	"3 2 1 4\n1 4 3 2\n2 3 4 1\n4 1 2 3\n",
	"3 2 1 4\n1 4 3 2\n4 1 2 3\n2 3 4 1\n",
	"3 2 1 4\n1 4 3 2\n4 3 2 1\n2 1 4 3\n",
	"3 2 1 4\n2 1 4 3\n1 4 3 2\n4 3 2 1\n",
	"3 2 1 4\n2 1 4 3\n4 3 2 1\n1 4 3 2\n",
	"3 2 1 4\n2 3 4 1\n1 4 2 3\n4 1 3 2\n",
	"3 2 1 4\n2 3 4 1\n1 4 3 2\n4 1 2 3\n",
	"3 2 1 4\n2 3 4 1\n4 1 2 3\n1 4 3 2\n",
	"3 2 1 4\n2 3 4 1\n4 1 3 2\n1 4 2 3\n",
	"3 2 1 4\n2 4 3 1\n1 3 4 2\n4 1 2 3\n",
	"3 2 1 4\n2 4 3 1\n4 1 2 3\n1 3 4 2\n",
	"3 2 1 4\n4 1 2 3\n1 3 4 2\n2 4 3 1\n",
	"3 2 1 4\n4 1 2 3\n1 4 3 2\n2 3 4 1\n",
	"3 2 1 4\n4 1 2 3\n2 3 4 1\n1 4 3 2\n",
	"3 2 1 4\n4 1 2 3\n2 4 3 1\n1 3 4 2\n",
	"3 2 1 4\n4 1 3 2\n1 4 2 3\n2 3 4 1\n",
	"3 2 1 4\n4 1 3 2\n2 3 4 1\n1 4 2 3\n",
	"3 2 1 4\n4 3 2 1\n1 4 3 2\n2 1 4 3\n",
	"3 2 1 4\n4 3 2 1\n2 1 4 3\n1 4 3 2\n",
	"3 2 4 1\n1 3 2 4\n2 4 1 3\n4 1 3 2\n",
	"3 2 4 1\n1 3 2 4\n4 1 3 2\n2 4 1 3\n",
	"3 2 4 1\n1 4 2 3\n2 1 3 4\n4 3 1 2\n",
	"3 2 4 1\n1 4 2 3\n2 3 1 4\n4 1 3 2\n",
	"3 2 4 1\n1 4 2 3\n4 1 3 2\n2 3 1 4\n",
	"3 2 4 1\n1 4 2 3\n4 3 1 2\n2 1 3 4\n",
	"3 2 4 1\n1 4 3 2\n2 3 1 4\n4 1 2 3\n",
	"3 2 4 1\n1 4 3 2\n4 1 2 3\n2 3 1 4\n",
	"3 2 4 1\n2 1 3 4\n1 4 2 3\n4 3 1 2\n",
	"3 2 4 1\n2 1 3 4\n4 3 1 2\n1 4 2 3\n",
	"3 2 4 1\n2 3 1 4\n1 4 2 3\n4 1 3 2\n",
	"3 2 4 1\n2 3 1 4\n1 4 3 2\n4 1 2 3\n",
	"3 2 4 1\n2 3 1 4\n4 1 2 3\n1 4 3 2\n",
	"3 2 4 1\n2 3 1 4\n4 1 3 2\n1 4 2 3\n",
	"3 2 4 1\n2 4 1 3\n1 3 2 4\n4 1 3 2\n",
	"3 2 4 1\n2 4 1 3\n4 1 3 2\n1 3 2 4\n",
	"3 2 4 1\n4 1 2 3\n1 4 3 2\n2 3 1 4\n",
	"3 2 4 1\n4 1 2 3\n2 3 1 4\n1 4 3 2\n",
	"3 2 4 1\n4 1 3 2\n1 3 2 4\n2 4 1 3\n",
	"3 2 4 1\n4 1 3 2\n1 4 2 3\n2 3 1 4\n",
	"3 2 4 1\n4 1 3 2\n2 3 1 4\n1 4 2 3\n",
	"3 2 4 1\n4 1 3 2\n2 4 1 3\n1 3 2 4\n",
	"3 2 4 1\n4 3 1 2\n1 4 2 3\n2 1 3 4\n",
	"3 2 4 1\n4 3 1 2\n2 1 3 4\n1 4 2 3\n",
	"3 4 1 2\n1 2 3 4\n2 1 4 3\n4 3 2 1\n",
	"3 4 1 2\n1 2 3 4\n2 3 4 1\n4 1 2 3\n",
	"3 4 1 2\n1 2 3 4\n4 1 2 3\n2 3 4 1\n",
	"3 4 1 2\n1 2 3 4\n4 3 2 1\n2 1 4 3\n",
	"3 4 1 2\n1 2 4 3\n2 1 3 4\n4 3 2 1\n",
	"3 4 1 2\n1 2 4 3\n4 3 2 1\n2 1 3 4\n",
	"3 4 1 2\n1 3 2 4\n2 1 4 3\n4 2 3 1\n",
	"3 4 1 2\n1 3 2 4\n4 2 3 1\n2 1 4 3\n",
	"3 4 1 2\n2 1 3 4\n1 2 4 3\n4 3 2 1\n",
	"3 4 1 2\n2 1 3 4\n4 3 2 1\n1 2 4 3\n",
	"3 4 1 2\n2 1 4 3\n1 2 3 4\n4 3 2 1\n",
	"3 4 1 2\n2 1 4 3\n1 3 2 4\n4 2 3 1\n",
	"3 4 1 2\n2 1 4 3\n4 2 3 1\n1 3 2 4\n",
	"3 4 1 2\n2 1 4 3\n4 3 2 1\n1 2 3 4\n",
	"3 4 1 2\n2 3 4 1\n1 2 3 4\n4 1 2 3\n",
	"3 4 1 2\n2 3 4 1\n4 1 2 3\n1 2 3 4\n",
	"3 4 1 2\n4 1 2 3\n1 2 3 4\n2 3 4 1\n",
	"3 4 1 2\n4 1 2 3\n2 3 4 1\n1 2 3 4\n",
	"3 4 1 2\n4 2 3 1\n1 3 2 4\n2 1 4 3\n",
	"3 4 1 2\n4 2 3 1\n2 1 4 3\n1 3 2 4\n",
	"3 4 1 2\n4 3 2 1\n1 2 3 4\n2 1 4 3\n",
	"3 4 1 2\n4 3 2 1\n1 2 4 3\n2 1 3 4\n",
	"3 4 1 2\n4 3 2 1\n2 1 3 4\n1 2 4 3\n",
	"3 4 1 2\n4 3 2 1\n2 1 4 3\n1 2 3 4\n",
	"3 4 2 1\n1 2 3 4\n2 1 4 3\n4 3 1 2\n",
	"3 4 2 1\n1 2 3 4\n4 3 1 2\n2 1 4 3\n",
	"3 4 2 1\n1 2 4 3\n2 1 3 4\n4 3 1 2\n",
	"3 4 2 1\n1 2 4 3\n2 3 1 4\n4 1 3 2\n",
	"3 4 2 1\n1 2 4 3\n4 1 3 2\n2 3 1 4\n",
	"3 4 2 1\n1 2 4 3\n4 3 1 2\n2 1 3 4\n",
	"3 4 2 1\n1 3 4 2\n2 1 3 4\n4 2 1 3\n",
	"3 4 2 1\n1 3 4 2\n4 2 1 3\n2 1 3 4\n",
	"3 4 2 1\n2 1 3 4\n1 2 4 3\n4 3 1 2\n",
	"3 4 2 1\n2 1 3 4\n1 3 4 2\n4 2 1 3\n",
	"3 4 2 1\n2 1 3 4\n4 2 1 3\n1 3 4 2\n",
	"3 4 2 1\n2 1 3 4\n4 3 1 2\n1 2 4 3\n",
	"3 4 2 1\n2 1 4 3\n1 2 3 4\n4 3 1 2\n",
	"3 4 2 1\n2 1 4 3\n4 3 1 2\n1 2 3 4\n",
	"3 4 2 1\n2 3 1 4\n1 2 4 3\n4 1 3 2\n",
	"3 4 2 1\n2 3 1 4\n4 1 3 2\n1 2 4 3\n",
	"3 4 2 1\n4 1 3 2\n1 2 4 3\n2 3 1 4\n",
	"3 4 2 1\n4 1 3 2\n2 3 1 4\n1 2 4 3\n",
	"3 4 2 1\n4 2 1 3\n1 3 4 2\n2 1 3 4\n",
	"3 4 2 1\n4 2 1 3\n2 1 3 4\n1 3 4 2\n",
	"3 4 2 1\n4 3 1 2\n1 2 3 4\n2 1 4 3\n",
	"3 4 2 1\n4 3 1 2\n1 2 4 3\n2 1 3 4\n",
	"3 4 2 1\n4 3 1 2\n2 1 3 4\n1 2 4 3\n",
	"3 4 2 1\n4 3 1 2\n2 1 4 3\n1 2 3 4\n",
	"4 1 2 3\n1 2 3 4\n2 3 4 1\n3 4 1 2\n",
	"4 1 2 3\n1 2 3 4\n3 4 1 2\n2 3 4 1\n",
	"4 1 2 3\n1 3 4 2\n2 4 3 1\n3 2 1 4\n",
	"4 1 2 3\n1 3 4 2\n3 2 1 4\n2 4 3 1\n",
	"4 1 2 3\n1 4 3 2\n2 3 1 4\n3 2 4 1\n",
	"4 1 2 3\n1 4 3 2\n2 3 4 1\n3 2 1 4\n",
	"4 1 2 3\n1 4 3 2\n3 2 1 4\n2 3 4 1\n",
	"4 1 2 3\n1 4 3 2\n3 2 4 1\n2 3 1 4\n",
	"4 1 2 3\n2 3 1 4\n1 4 3 2\n3 2 4 1\n",
	"4 1 2 3\n2 3 1 4\n3 2 4 1\n1 4 3 2\n",
	"4 1 2 3\n2 3 4 1\n1 2 3 4\n3 4 1 2\n",
	"4 1 2 3\n2 3 4 1\n1 4 3 2\n3 2 1 4\n",
	"4 1 2 3\n2 3 4 1\n3 2 1 4\n1 4 3 2\n",
	"4 1 2 3\n2 3 4 1\n3 4 1 2\n1 2 3 4\n",
	"4 1 2 3\n2 4 3 1\n1 3 4 2\n3 2 1 4\n",
	"4 1 2 3\n2 4 3 1\n3 2 1 4\n1 3 4 2\n",
	"4 1 2 3\n3 2 1 4\n1 3 4 2\n2 4 3 1\n",
	"4 1 2 3\n3 2 1 4\n1 4 3 2\n2 3 4 1\n",
	"4 1 2 3\n3 2 1 4\n2 3 4 1\n1 4 3 2\n",
	"4 1 2 3\n3 2 1 4\n2 4 3 1\n1 3 4 2\n",
	"4 1 2 3\n3 2 4 1\n1 4 3 2\n2 3 1 4\n",
	"4 1 2 3\n3 2 4 1\n2 3 1 4\n1 4 3 2\n",
	"4 1 2 3\n3 4 1 2\n1 2 3 4\n2 3 4 1\n",
	"4 1 2 3\n3 4 1 2\n2 3 4 1\n1 2 3 4\n",
	"4 1 3 2\n1 2 4 3\n2 3 1 4\n3 4 2 1\n",
	"4 1 3 2\n1 2 4 3\n3 4 2 1\n2 3 1 4\n",
	"4 1 3 2\n1 3 2 4\n2 4 1 3\n3 2 4 1\n",
	"4 1 3 2\n1 3 2 4\n3 2 4 1\n2 4 1 3\n",
	"4 1 3 2\n1 4 2 3\n2 3 1 4\n3 2 4 1\n",
	"4 1 3 2\n1 4 2 3\n2 3 4 1\n3 2 1 4\n",
	"4 1 3 2\n1 4 2 3\n3 2 1 4\n2 3 4 1\n",
	"4 1 3 2\n1 4 2 3\n3 2 4 1\n2 3 1 4\n",
	"4 1 3 2\n2 3 1 4\n1 2 4 3\n3 4 2 1\n",
	"4 1 3 2\n2 3 1 4\n1 4 2 3\n3 2 4 1\n",
	"4 1 3 2\n2 3 1 4\n3 2 4 1\n1 4 2 3\n",
	"4 1 3 2\n2 3 1 4\n3 4 2 1\n1 2 4 3\n",
	"4 1 3 2\n2 3 4 1\n1 4 2 3\n3 2 1 4\n",
	"4 1 3 2\n2 3 4 1\n3 2 1 4\n1 4 2 3\n",
	"4 1 3 2\n2 4 1 3\n1 3 2 4\n3 2 4 1\n",
	"4 1 3 2\n2 4 1 3\n3 2 4 1\n1 3 2 4\n",
	"4 1 3 2\n3 2 1 4\n1 4 2 3\n2 3 4 1\n",
	"4 1 3 2\n3 2 1 4\n2 3 4 1\n1 4 2 3\n",
	"4 1 3 2\n3 2 4 1\n1 3 2 4\n2 4 1 3\n",
	"4 1 3 2\n3 2 4 1\n1 4 2 3\n2 3 1 4\n",
	"4 1 3 2\n3 2 4 1\n2 3 1 4\n1 4 2 3\n",
	"4 1 3 2\n3 2 4 1\n2 4 1 3\n1 3 2 4\n",
	"4 1 3 2\n3 4 2 1\n1 2 4 3\n2 3 1 4\n",
	"4 1 3 2\n3 4 2 1\n2 3 1 4\n1 2 4 3\n",
	"4 2 1 3\n1 3 2 4\n2 4 3 1\n3 1 4 2\n",
	"4 2 1 3\n1 3 2 4\n3 1 4 2\n2 4 3 1\n",
	"4 2 1 3\n1 3 4 2\n2 1 3 4\n3 4 2 1\n",
	"4 2 1 3\n1 3 4 2\n2 4 3 1\n3 1 2 4\n",
	"4 2 1 3\n1 3 4 2\n3 1 2 4\n2 4 3 1\n",
	"4 2 1 3\n1 3 4 2\n3 4 2 1\n2 1 3 4\n",
	"4 2 1 3\n1 4 3 2\n2 3 4 1\n3 1 2 4\n",
	"4 2 1 3\n1 4 3 2\n3 1 2 4\n2 3 4 1\n",
	"4 2 1 3\n2 1 3 4\n1 3 4 2\n3 4 2 1\n",
	"4 2 1 3\n2 1 3 4\n3 4 2 1\n1 3 4 2\n",
	"4 2 1 3\n2 3 4 1\n1 4 3 2\n3 1 2 4\n",
	"4 2 1 3\n2 3 4 1\n3 1 2 4\n1 4 3 2\n",
	"4 2 1 3\n2 4 3 1\n1 3 2 4\n3 1 4 2\n",
	"4 2 1 3\n2 4 3 1\n1 3 4 2\n3 1 2 4\n",
	"4 2 1 3\n2 4 3 1\n3 1 2 4\n1 3 4 2\n",
	"4 2 1 3\n2 4 3 1\n3 1 4 2\n1 3 2 4\n",
	"4 2 1 3\n3 1 2 4\n1 3 4 2\n2 4 3 1\n",
	"4 2 1 3\n3 1 2 4\n1 4 3 2\n2 3 4 1\n",
	"4 2 1 3\n3 1 2 4\n2 3 4 1\n1 4 3 2\n",
	"4 2 1 3\n3 1 2 4\n2 4 3 1\n1 3 4 2\n",
	"4 2 1 3\n3 1 4 2\n1 3 2 4\n2 4 3 1\n",
	"4 2 1 3\n3 1 4 2\n2 4 3 1\n1 3 2 4\n",
	"4 2 1 3\n3 4 2 1\n1 3 4 2\n2 1 3 4\n",
	"4 2 1 3\n3 4 2 1\n2 1 3 4\n1 3 4 2\n",
	"4 2 3 1\n1 3 2 4\n2 1 4 3\n3 4 1 2\n",
	"4 2 3 1\n1 3 2 4\n2 4 1 3\n3 1 4 2\n",
	"4 2 3 1\n1 3 2 4\n3 1 4 2\n2 4 1 3\n",
	"4 2 3 1\n1 3 2 4\n3 4 1 2\n2 1 4 3\n",
	"4 2 3 1\n1 3 4 2\n2 4 1 3\n3 1 2 4\n",
	"4 2 3 1\n1 3 4 2\n3 1 2 4\n2 4 1 3\n",
	"4 2 3 1\n1 4 2 3\n2 3 1 4\n3 1 4 2\n",
	"4 2 3 1\n1 4 2 3\n3 1 4 2\n2 3 1 4\n",
	"4 2 3 1\n2 1 4 3\n1 3 2 4\n3 4 1 2\n",
	"4 2 3 1\n2 1 4 3\n3 4 1 2\n1 3 2 4\n",
	"4 2 3 1\n2 3 1 4\n1 4 2 3\n3 1 4 2\n",
	"4 2 3 1\n2 3 1 4\n3 1 4 2\n1 4 2 3\n",
	"4 2 3 1\n2 4 1 3\n1 3 2 4\n3 1 4 2\n",
	"4 2 3 1\n2 4 1 3\n1 3 4 2\n3 1 2 4\n",
	"4 2 3 1\n2 4 1 3\n3 1 2 4\n1 3 4 2\n",
	"4 2 3 1\n2 4 1 3\n3 1 4 2\n1 3 2 4\n",
	"4 2 3 1\n3 1 2 4\n1 3 4 2\n2 4 1 3\n",
	"4 2 3 1\n3 1 2 4\n2 4 1 3\n1 3 4 2\n",
	"4 2 3 1\n3 1 4 2\n1 3 2 4\n2 4 1 3\n",
	"4 2 3 1\n3 1 4 2\n1 4 2 3\n2 3 1 4\n",
	"4 2 3 1\n3 1 4 2\n2 3 1 4\n1 4 2 3\n",
	"4 2 3 1\n3 1 4 2\n2 4 1 3\n1 3 2 4\n",
	"4 2 3 1\n3 4 1 2\n1 3 2 4\n2 1 4 3\n",
	"4 2 3 1\n3 4 1 2\n2 1 4 3\n1 3 2 4\n",
	"4 3 1 2\n1 2 3 4\n2 1 4 3\n3 4 2 1\n",
	"4 3 1 2\n1 2 3 4\n3 4 2 1\n2 1 4 3\n",
	"4 3 1 2\n1 2 4 3\n2 1 3 4\n3 4 2 1\n",
	"4 3 1 2\n1 2 4 3\n2 4 3 1\n3 1 2 4\n",
	"4 3 1 2\n1 2 4 3\n3 1 2 4\n2 4 3 1\n",
	"4 3 1 2\n1 2 4 3\n3 4 2 1\n2 1 3 4\n",
	"4 3 1 2\n1 4 2 3\n2 1 3 4\n3 2 4 1\n",
	"4 3 1 2\n1 4 2 3\n3 2 4 1\n2 1 3 4\n",
	"4 3 1 2\n2 1 3 4\n1 2 4 3\n3 4 2 1\n",
	"4 3 1 2\n2 1 3 4\n1 4 2 3\n3 2 4 1\n",
	"4 3 1 2\n2 1 3 4\n3 2 4 1\n1 4 2 3\n",
	"4 3 1 2\n2 1 3 4\n3 4 2 1\n1 2 4 3\n",
	"4 3 1 2\n2 1 4 3\n1 2 3 4\n3 4 2 1\n",
	"4 3 1 2\n2 1 4 3\n3 4 2 1\n1 2 3 4\n",
	"4 3 1 2\n2 4 3 1\n1 2 4 3\n3 1 2 4\n",
	"4 3 1 2\n2 4 3 1\n3 1 2 4\n1 2 4 3\n",
	"4 3 1 2\n3 1 2 4\n1 2 4 3\n2 4 3 1\n",
	"4 3 1 2\n3 1 2 4\n2 4 3 1\n1 2 4 3\n",
	"4 3 1 2\n3 2 4 1\n1 4 2 3\n2 1 3 4\n",
	"4 3 1 2\n3 2 4 1\n2 1 3 4\n1 4 2 3\n",
	"4 3 1 2\n3 4 2 1\n1 2 3 4\n2 1 4 3\n",
	"4 3 1 2\n3 4 2 1\n1 2 4 3\n2 1 3 4\n",
	"4 3 1 2\n3 4 2 1\n2 1 3 4\n1 2 4 3\n",
	"4 3 1 2\n3 4 2 1\n2 1 4 3\n1 2 3 4\n",
	"4 3 2 1\n1 2 3 4\n2 1 4 3\n3 4 1 2\n",
	"4 3 2 1\n1 2 3 4\n2 4 1 3\n3 1 4 2\n",
	"4 3 2 1\n1 2 3 4\n3 1 4 2\n2 4 1 3\n",
	"4 3 2 1\n1 2 3 4\n3 4 1 2\n2 1 4 3\n",
	"4 3 2 1\n1 2 4 3\n2 1 3 4\n3 4 1 2\n",
	"4 3 2 1\n1 2 4 3\n3 4 1 2\n2 1 3 4\n",
	"4 3 2 1\n1 4 3 2\n2 1 4 3\n3 2 1 4\n",
	"4 3 2 1\n1 4 3 2\n3 2 1 4\n2 1 4 3\n",
	"4 3 2 1\n2 1 3 4\n1 2 4 3\n3 4 1 2\n",
	"4 3 2 1\n2 1 3 4\n3 4 1 2\n1 2 4 3\n",
	"4 3 2 1\n2 1 4 3\n1 2 3 4\n3 4 1 2\n",
	"4 3 2 1\n2 1 4 3\n1 4 3 2\n3 2 1 4\n",
	"4 3 2 1\n2 1 4 3\n3 2 1 4\n1 4 3 2\n",
	"4 3 2 1\n2 1 4 3\n3 4 1 2\n1 2 3 4\n",
	"4 3 2 1\n2 4 1 3\n1 2 3 4\n3 1 4 2\n",
	"4 3 2 1\n2 4 1 3\n3 1 4 2\n1 2 3 4\n",
	"4 3 2 1\n3 1 4 2\n1 2 3 4\n2 4 1 3\n",
	"4 3 2 1\n3 1 4 2\n2 4 1 3\n1 2 3 4\n",
	"4 3 2 1\n3 2 1 4\n1 4 3 2\n2 1 4 3\n",
	"4 3 2 1\n3 2 1 4\n2 1 4 3\n1 4 3 2\n",
	"4 3 2 1\n3 4 1 2\n1 2 3 4\n2 1 4 3\n",
	"4 3 2 1\n3 4 1 2\n1 2 4 3\n2 1 3 4\n",
	"4 3 2 1\n3 4 1 2\n2 1 3 4\n1 2 4 3\n",
	"4 3 2 1\n3 4 1 2\n2 1 4 3\n1 2 3 4\n",
	};

const unsigned int	inputs[576] = {0xd417d417, 0xd41ad41a, 0xa447d11a,
	0xa44ad11d, 0xe415e415, 0xa44ae115, 0xd417d417, 0x9462d11d, 0x9416d417,
	0xa449d11d, 0x9416d417, 0x9425d815, 0x9452d215, 0x9461d11d, 0x9416d426,
	0x9461d129, 0x6446c915, 0x5493c615, 0x6446c526, 0x6491c529, 0x6446c535,
	0x6452c535, 0x6485c535, 0x6491c535, 0xd11aa447, 0xd11da44a, 0xa14aa14a,
	0xa14da14d, 0xe115a44a, 0xa14aa14a, 0xd11d9462, 0x91689168, 0x9119944a,
	0xa146914a, 0x91199853, 0x9164925c, 0x91199862, 0x91259862, 0x91589268,
	0x91649268, 0x61498962, 0x519c8668, 0x61498962, 0x61588568, 0x61858562,
	0x61948668, 0x61498971, 0x61948674, 0xd4179416, 0x944a9119, 0xd4179416,
	0xd4269416, 0x98539119, 0x98629119, 0xd8159425, 0x98629125, 0x94169416,
	0x94199419, 0x94469116, 0x94499119, 0x94169416, 0x94499119, 0x94169416,
	0x98619119, 0x58528525, 0x58858525, 0x58528519, 0x54878516, 0x58468525,
	0x58528525, 0x58858525, 0x58918525, 0xd11da449, 0x914aa146, 0xd2159452,
	0x92689158, 0xd11d9461, 0xd1299461, 0x925c9164, 0x92689164, 0x91169446,
	0x91199449, 0x91469146, 0x91499149, 0x91199449, 0x91469146, 0x91199861,
	0x92649264, 0x52588558, 0x52858552, 0x52498952, 0x52588558, 0x52858552,
	0x52948658, 0x52588564, 0x518d8561, 0xc9156446, 0x89626149, 0xc5266446,
	0xc5356446, 0x89626149, 0x89716149, 0xc5356452, 0x85686158, 0x85255852,
	0x85585258, 0x85255846, 0x89525249, 0x85195852, 0x85255852, 0x85585258,
	0x85645258, 0x49614961, 0x49644964, 0x49914661, 0x49944664, 0x49614961,
	0x49944664, 0x49614961, 0x45b44664, 0xc6155493, 0x8668519c, 0xc5356485,
	0x85626185, 0xc5296491, 0xc5356491, 0x86686194, 0x86746194, 0x85255885,
	0x85525285, 0x85165487, 0x85255885, 0x85525285, 0x8561518d, 0x85255891,
	0x86585294, 0x46614991, 0x46644994, 0x46914691, 0x46944694, 0x46644994,
	0x46914691, 0x466445b4, 0x45b145b1, 0xa417a417, 0xa41aa41a, 0x7447a11a,
	0x744aa11d, 0xa419a419, 0x6446a116, 0x94169416, 0x54639119, 0xa41a9416,
	0xb4459119, 0x94169817, 0x9461921d, 0x94169826, 0x94259825, 0x94529225,
	0x94619229, 0x74478916, 0x64928619, 0x64468926, 0x64528525, 0x64858525,
	0x64918629, 0x64468935, 0x64918635, 0xa11a7447, 0xa11d744a, 0x714a714a,
	0x714d714d, 0xa1166446, 0x61496149, 0x91195463, 0x516c516c, 0xa11a544b,
	0xb145514e, 0x91195c53, 0x91255852, 0x91585258, 0x9164535c, 0x91195c62,
	0x91645368, 0x714d4961, 0x61984664, 0x61494d62, 0x61944768, 0x61494d71,
	0x61584578, 0x61854572, 0x61944774, 0x9416a41a, 0x544ba11a, 0x98179416,
	0x98269416, 0x5c539119, 0x5c629119, 0x98259425, 0x58529125, 0x94169416,
	0x94499119, 0x94169416, 0x94199419, 0x94469116, 0x94499119, 0x98269826,
	0x9c519229, 0x5c538519, 0x58868516, 0x58468926, 0x58528525, 0x58858525,
	0x58918629, 0x58528525, 0x58858525, 0x9119b445, 0x514eb145, 0x92259452,
	0x52589158, 0x921d9461, 0x92299461, 0x535c9164, 0x53689164, 0x91199449,
	0x91469146, 0x91169446, 0x91199449, 0x91469146, 0x91499149, 0x92299c51,
	0x93549354, 0x52498d51, 0x52588558, 0x52858552, 0x52948754, 0x535c8564,
	0x52898561, 0x52588558, 0x52858552, 0x89167447, 0x4961714d, 0x89266446,
	0x89356446, 0x4d626149, 0x4d716149, 0x85256452, 0x45786158, 0x89265846,
	0x8d515249, 0x85195c53, 0x85255852, 0x85585258, 0x8564535c, 0x85255852,
	0x85585258, 0x49614961, 0x49944664, 0x49614961, 0x49644964, 0x49914661,
	0x49944664, 0x4d714d71, 0x49a44774, 0x86196492, 0x46646198, 0x85256485,
	0x45726185, 0x86296491, 0x86356491, 0x47686194, 0x47746194, 0x85165886,
	0x85255885, 0x85525285, 0x85615289, 0x86295891, 0x87545294, 0x85255885,
	0x85525285, 0x46644994, 0x46914691, 0x46614991, 0x46644994, 0x46914691,
	0x46944694, 0x477449a4, 0x46a146a1, 0x641a641a, 0x7447611a, 0x64166416,
	0x64196419, 0x64466116, 0x64496119, 0x58255825, 0x58525225, 0x64196419,
	0x64466116, 0x54275816, 0x58525219, 0x58165826, 0x58255825, 0x58525225,
	0x58615229, 0x74474916, 0x68534619, 0x74864916, 0x68924619, 0x78454925,
	0x68924625, 0x64464926, 0x68914629, 0x611a7447, 0x714d714d, 0x61166446,
	0x61196449, 0x61466146, 0x61496149, 0x52255852, 0x52585258, 0x61166446,
	0x61496149, 0x52195c53, 0x52255852, 0x52585258, 0x5264535c, 0x512d5861,
	0x52585264, 0x72454952, 0x62984658, 0x714d4961, 0x625c4664, 0x71894961,
	0x62984664, 0x61494d71, 0x62944774, 0x64196419, 0x64466116, 0x58265816,
	0x5c535219, 0x58165427, 0x58255825, 0x58525225, 0x5861512d, 0x541b541b,
	0x6446511e, 0x64166416, 0x64196419, 0x64466116, 0x64496119, 0x58255825,
	0x58525225, 0x68474916, 0x5c534619, 0x68864916, 0x5c924619, 0x58524625,
	0x68854925, 0x6c514539, 0x68864536, 0x61166446, 0x61496149, 0x52195852,
	0x52255852, 0x52585258, 0x52645258, 0x52295861, 0x535c5264, 0x511e6446,
	0x61496149, 0x61166446, 0x61196449, 0x61466146, 0x61496149, 0x52255852,
	0x52585258, 0x52584658, 0x62854952, 0x624d4961, 0x535c4664, 0x62894961,
	0x53984664, 0x63544664, 0x62894961, 0x49167447, 0x49257845, 0x49527245,
	0x4961714d, 0x46196853, 0x4664625c, 0x49266446, 0x4d716149, 0x49166847,
	0x4961624d, 0x46195c53, 0x46255852, 0x46585258, 0x4664535c, 0x45396c51,
	0x46646354, 0x4e514e51, 0x4aa44b54, 0x49614961, 0x4a944664, 0x4d714d71,
	0x4a744a74, 0x4da14a71, 0x4aa44774, 0x49167486, 0x49617189, 0x46196892,
	0x46256892, 0x46586298, 0x46646298, 0x46296891, 0x47746294, 0x49166886,
	0x49256885, 0x49526285, 0x49616289, 0x46195c92, 0x46645398, 0x45366886,
	0x49616289, 0x4b544aa4, 0x4aa14aa1, 0x46644a94, 0x4a914a91, 0x4a714da1,
	0x47744aa4, 0x4aa14aa1, 0x47a447a4, 0x39453945, 0x29923645, 0x25582558,
	0x25852552, 0x19611961, 0x19641964, 0x19911661, 0x19941664, 0x29522549,
	0x25852546, 0x25492d51, 0x25582558, 0x25852552, 0x25942754, 0x19641964,
	0x19911661, 0x35861946, 0x29921649, 0x35c51946, 0x29d11649, 0x25981658,
	0x35c51952, 0x19911e51, 0x15e41b54, 0x36452992, 0x26982698, 0x25522585,
	0x25852585, 0x16611991, 0x16641994, 0x16911691, 0x16941694, 0x25462986,
	0x25522585, 0x25852585, 0x25912689, 0x26582594, 0x25852591, 0x16611991,
	0x16941694, 0x25921685, 0x35c51985, 0x35891991, 0x26981694, 0x35c51991,
	0x26d41694, 0x16941aa4, 0x15e11aa1, 0x2d512549, 0x29862546, 0x25492952,
	0x25582558, 0x25852552, 0x25942658, 0x19641964, 0x19911661, 0x29462946,
	0x19912649, 0x25582558, 0x25852552, 0x19611961, 0x19641964, 0x19911661,
	0x19941664, 0x29861946, 0x1d921649, 0x29c51946, 0x1dd11649, 0x25851952,
	0x15d81658, 0x19a41a64, 0x1dd11a61, 0x25462585, 0x25522585, 0x25852585,
	0x25912585, 0x27542594, 0x26892591, 0x16611991, 0x16941694, 0x26491991,
	0x16941694, 0x25522585, 0x25852585, 0x16611991, 0x16641994, 0x16911691,
	0x16941694, 0x25851985, 0x15d21685, 0x26891991, 0x17981694, 0x26c51991,
	0x17d41694, 0x16a11991, 0x17d41694, 0x19463586, 0x19913589, 0x16492992,
	0x16582598, 0x16852592, 0x16942698, 0x1e511991, 0x1aa41694, 0x19462986,
	0x19522585, 0x19852585, 0x19912689, 0x16491d92, 0x16941798, 0x1a6419a4,
	0x199116a1, 0x19861986, 0x1dd11689, 0x16941694, 0x15c91991, 0x1da11da1,
	0x1aa41aa4, 0x1dd11aa1, 0x1ad417a4, 0x194635c5, 0x195235c5, 0x198535c5,
	0x199135c5, 0x164929d1, 0x169426d4, 0x1b5415e4, 0x1aa115e1, 0x194629c5,
	0x199126c5, 0x16491dd1, 0x165815d8, 0x168515d2, 0x169417d4, 0x1a611dd1,
	0x169417d4, 0x16891dd1, 0x17d417d4, 0x199115c9, 0x15c615c6, 0x1aa11dd1,
	0x17a41ad4, 0x1ad11ad1, 0x17d417d4};


//	helper functions to generate the array of solutions, and inputs
//	not needed for the actual program

// static int	test_sqr(unsigned int u, unsigned int in[576], int i)
// {
// 	if (((1 << M00(u)) | (1 << M01(u)) | (1 << M02(u)) | (1 << M03(u))) ^ 15
// 		|| ((1 << M10(u)) | (1 << M11(u)) | (1 << M12(u)) | (1 << M13(u))) ^ 15
// 		|| ((1 << M20(u)) | (1 << M21(u)) | (1 << M22(u)) | (1 << M23(u))) ^ 15
// 		|| ((1 << M30(u)) | (1 << M31(u)) | (1 << M32(u)) | (1 << M33(u))) ^ 15
// 		|| ((1 << M00(u)) | (1 << M10(u)) | (1 << M20(u)) | (1 << M30(u))) ^ 15
// 		|| ((1 << M01(u)) | (1 << M11(u)) | (1 << M21(u)) | (1 << M31(u))) ^ 15
// 		|| ((1 << M02(u)) | (1 << M12(u)) | (1 << M22(u)) | (1 << M32(u))) ^ 15
// 		|| ((1 << M03(u)) | (1 << M13(u)) | (1 << M23(u)) | (1 << M33(u))) ^ 15
// 		)
// 		return (0);
// 	else
// 	{
// 		in[i] = C1U(u) << 30 | C2U(u) << 28 | C3U(u) << 26 | C4U(u) << 24
// 			| C1D(u) << 22 | C2D(u) << 20 | C3D(u) << 18 | C4D(u) << 16
// 			| C1L(u) << 14 | C2L(u) << 12 | C3L(u) << 10 | C4L(u) << 8
// 			| C1R(u) << 6 | C2R(u) << 4 | C3R(u) << 2 | C4R(u);
// 		return (1);
// 	}
// }

// static void	print_solutions(unsigned int sol[576])
// {
// 	int				i;
// 	unsigned int	u;

// 	i = 0;
// 	printf("const unsigned char\tsolutions[576][33] = {\n");
// 	while (i < 576)
// 	{
// 		u = sol[i];
// 		printf ("\"%i %i %i %i\\n",
// 			M00(u) + 1, M01(u) + 1, M02(u) + 1, M03(u) + 1);
// 		printf ("%i %i %i %i\\n",
// 			M10(u) + 1, M11(u) + 1, M12(u) + 1, M13(u) + 1);
// 		printf ("%i %i %i %i\\n",
// 			M20(u) + 1, M21(u) + 1, M22(u) + 1, M23(u) + 1);
// 		printf ("%i %i %i %i\\n\"",
// 			M30(u) + 1, M31(u) + 1, M32(u) + 1, M33(u) + 1);
// 		printf (",\n\t");
// 		++i;
// 	}
// 	printf("};\n");
// }

// static void	print_inputs(unsigned int in[576])
// {
// 	int	i;

// 	i = 0;
// 	printf("const unsigned int\tinputs[576] = {");
// 	while (i < 576)
// 	{
// 		printf ("%#x", in[i]);
// 		++i;
// 		if ((i % 6) == 3)
// 			printf (",\n\t");
// 		else if (i < 576)
// 			printf(", ");
// 	}
// 	printf("};\n");
// }

// static void	generate_solutions(void)
// {
// 	unsigned int	u;
// 	unsigned int	sol[576];
// 	unsigned int	in[576];
// 	int				i;

// 	u = 0;
// 	i = 0;
// 	while (u < 0xFFFFFFFF)
// 	{
// 		if (test_sqr(u, in, i))
// 		{
// 			sol[i] = u;
// 			++i;
// 		}
// 		++u;
// 	}
// 	print_solutions(sol);
// 	print_inputs(in);
// }

int	main(int argc, char *argv[])
{
	unsigned int	input;
	int				i;

	if (argc ^ 2)
	{
		write (2, "Error\n", 6);
		return (WRONG_NUMBER_OF_ARGUMENTS);
	}
	i = 0;
	input = 0;
	while (i < 16)
	{
		if (argv[1][2 * i] < '1' || argv[1][2 * i] > '4'
			|| ((argv[1][2 * i + 1] ^ ' ') && (i < 15)))
			break ;
		input |= (unsigned char)argv[1][2 * i] - (unsigned char)'1';
		if (i < 15)
			input <<= 2;
		++i;
	}
	if (i ^ 16)
	{
		write (2, "Error\n", 6);
		return (WRONG_INPUT);
	}
	i = -1;
	while (++i < 576)
	{
		if (input == inputs[i])
		{
			write(1, solutions[i], 32);
			return (SUCCESS);
		}
	}
	write (2, "Error\n", 6);
	return (NO_SOLUTION);
}