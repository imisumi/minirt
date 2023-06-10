
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:16:03 by imisumi           #+#    #+#             */
/*   Updated: 2023/06/09 15:59:13 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_mat4	fill_mat4(t_mat4 m, float f) {
	int i;
	int j;

	i = 0;
	while (i < 4) {
		j = 0;
		while (j < 4) {
			m.m[i][j] = f;
			j++;
		}
		i++;
	}
	return (m);
}

t_mat4	create_mat4(float f) {
	t_mat4 m;

	m = fill_mat4(m, f);
	return (m);
}

t_mat4 mat4_identity()
{
	t_mat4 result = create_mat4(0.0f);
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	return result;
}

t_mat4 mat4_translate(t_vec3 translation)
{
    t_mat4 result = mat4_identity();
    result.m[3][0] = translation.x;
    result.m[3][1] = translation.y;
    result.m[3][2] = translation.z;
    return result;
}
// t_mat4 mat4_translate(t_vec3 translation)
// {
// 	t_mat4 result = mat4_identity();
// 	result.m[0][3] = translation.x;
// 	result.m[1][3] = translation.y;
// 	result.m[2][3] = translation.z;
// 	return (result);
// }

// t_mat4 mat4_lookAt(t_vec3 eye, t_vec3 target, t_vec3 up)



t_mat4 mat4_lookAt(t_vec3 pos, t_vec3 target, t_vec3 up)
{
    t_vec3 f = vec3_add(target, vec3_mul_float(pos, -1.0f));
    t_vec3 f_normalized = vec3_normalize(f);

    t_vec3 s = vec3_cross(f_normalized, up);
    t_vec3 s_normalized = vec3_normalize(s);

    t_vec3 u = vec3_cross(s_normalized, f_normalized);

    t_mat4 result = mat4_identity();
    result.m[0][0] = s_normalized.x;
    result.m[1][0] = s_normalized.y;
    result.m[2][0] = s_normalized.z;
    result.m[0][1] = u.x;
    result.m[1][1] = u.y;
    result.m[2][1] = u.z;
    result.m[0][2] = -f_normalized.x;
    result.m[1][2] = -f_normalized.y;
    result.m[2][2] = -f_normalized.z;
	//! might be wrong
    // result.m[3][0] = -vec3_dot(s_normalized, pos);
	result.m[3][0] = -vec3_dot_float(s_normalized, pos);
    result.m[3][1] = -vec3_dot_float(u, pos);
    result.m[3][2] = vec3_dot_float(f_normalized, pos);

    return result;
}

float determinant(const t_mat4 matrix)
{
	return matrix.m[0][0] * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) -
			matrix.m[0][1] * (matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) +
			matrix.m[0][2] * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);
}

// t_mat4 inverse_mat4(t_mat4 matrix)
// {
//     t_mat4 result;
//     float det;

//     result.m[0][0] = matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] -
//                      matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2] -
//                      matrix.m[2][1] * matrix.m[1][2] * matrix.m[3][3] +
//                      matrix.m[2][1] * matrix.m[1][3] * matrix.m[3][2] +
//                      matrix.m[3][1] * matrix.m[1][2] * matrix.m[2][3] -
//                      matrix.m[3][1] * matrix.m[1][3] * matrix.m[2][2];

//     result.m[0][1] = -matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][3] +
//                      matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][2] +
//                      matrix.m[2][1] * matrix.m[0][2] * matrix.m[3][3] -
//                      matrix.m[2][1] * matrix.m[0][3] * matrix.m[3][2] -
//                      matrix.m[3][1] * matrix.m[0][2] * matrix.m[2][3] +
//                      matrix.m[3][1] * matrix.m[0][3] * matrix.m[2][2];

//     result.m[0][2] = matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][3] -
//                      matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][2] -
//                      matrix.m[1][1] * matrix.m[0][2] * matrix.m[3][3] +
//                      matrix.m[1][1] * matrix.m[0][3] * matrix.m[3][2] +
//                      matrix.m[3][1] * matrix.m[0][2] * matrix.m[1][3] -
//                      matrix.m[3][1] * matrix.m[0][3] * matrix.m[1][2];

//     result.m[0][3] = -matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] +
//                      matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2] +
//                      matrix.m[1][1] * matrix.m[0][2] * matrix.m[2][3] -
//                      matrix.m[1][1] * matrix.m[0][3] * matrix.m[2][2] -
//                      matrix.m[2][1] * matrix.m[0][2] * matrix.m[1][3] +
//                      matrix.m[2][1] * matrix.m[0][3] * matrix.m[1][2];

//     result.m[1][0] = -matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] +
//                      matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2] +
//                      matrix.m[2][0] * matrix.m[1][2] * matrix.m[3][3] -
//                      matrix.m[2][0] * matrix.m[1][3] * matrix.m[3][2] -
//                      matrix.m[3][0] * matrix.m[1][2] * matrix.m[2][3] +
//                      matrix.m[3][0] * matrix.m[1][3] * matrix.m[2][2];

//     result.m[1][1] = matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][3] -
//                      matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][2] -
//                      matrix.m[2][0] * matrix.m[0][2] * matrix.m[3][3] +
//                      matrix.m[2][0] * matrix.m[0][3] * matrix.m[3][2] +
//                      matrix.m[3][0] * matrix.m[0][2] * matrix.m[2][3] -
//                      matrix.m[3][0] * matrix.m[0][3] * matrix.m[2][2];

//     result.m[1][2] = -matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][3] +
//                      matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][2] +
//                      matrix.m[1][0] * matrix.m[0][2] * matrix.m[3][3] -
//                      matrix.m[1][0] * matrix.m[0][3] * matrix.m[3][2] -
//                      matrix.m[3][0] * matrix.m[0][2] * matrix.m[1][3] +
//                      matrix.m[3][0] * matrix.m[0][3] * matrix.m[1][2];

//     result.m[1][3] = matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] -
//                      matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2] -
//                      matrix.m[1][0] * matrix.m[0][2] * matrix.m[2][3] +
//                      matrix.m[1][0] * matrix.m[0][3] * matrix.m[2][2] +
//                      matrix.m[2][0] * matrix.m[0][2] * matrix.m[1][3] -
//                      matrix.m[2][0] * matrix.m[0][3] * matrix.m[1][2];

//     result.m[2][0] = matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] -
//                      matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1] -
//                      matrix.m[2][0] * matrix.m[1][1] * matrix.m[3][3] +
//                      matrix.m[2][0] * matrix.m[1][3] * matrix.m[3][1] +
//                      matrix.m[3][0] * matrix.m[1][1] * matrix.m[2][3] -
//                      matrix.m[3][0] * matrix.m[1][3] * matrix.m[2][1];

//     result.m[2][1] = -matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][3] +
//                      matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][1] +
//                      matrix.m[2][0] * matrix.m[0][1] * matrix.m[3][3] -
//                      matrix.m[2][0] * matrix.m[0][3] * matrix.m[3][1] -
//                      matrix.m[3][0] * matrix.m[0][1] * matrix.m[2][3] +
//                      matrix.m[3][0] * matrix.m[0][3] * matrix.m[2][1];

//     result.m[2][2] = matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][3] -
//                      matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][1] -
//                      matrix.m[1][0] * matrix.m[0][1] * matrix.m[3][3] +
//                      matrix.m[1][0] * matrix.m[0][3] * matrix.m[3][1] +
//                      matrix.m[3][0] * matrix.m[0][1] * matrix.m[1][3] -
//                      matrix.m[3][0] * matrix.m[0][3] * matrix.m[1][1];

//     result.m[2][3] = -matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] +
//                      matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1] +
//                      matrix.m[1][0] * matrix.m[0][1] * matrix.m[2][3] -
//                      matrix.m[1][0] * matrix.m[0][3] * matrix.m[2][1] -
//                      matrix.m[2][0] * matrix.m[0][1] * matrix.m[1][3] +
//                      matrix.m[2][0] * matrix.m[0][3] * matrix.m[1][1];

//     result.m[3][0] = -matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] +
//                      matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1] +
//                      matrix.m[2][0] * matrix.m[1][1] * matrix.m[3][2] -
//                      matrix.m[2][0] * matrix.m[1][2] * matrix.m[3][1] -
//                      matrix.m[3][0] * matrix.m[1][1] * matrix.m[2][2] +
//                      matrix.m[3][0] * matrix.m[1][2] * matrix.m[2][1];

//     result.m[3][1] = matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][2] -
//                      matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][1] -
//                      matrix.m[2][0] * matrix.m[0][1] * matrix.m[3][2] +
//                      matrix.m[2][0] * matrix.m[0][2] * matrix.m[3][1] +
//                      matrix.m[3][0] * matrix.m[0][1] * matrix.m[2][2] -
//                      matrix.m[3][0] * matrix.m[0][2] * matrix.m[2][1];

//     result.m[3][2] = -matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][2] +
//                      matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][1] +
//                      matrix.m[1][0] * matrix.m[0][1] * matrix.m[3][2] -
//                      matrix.m[1][0] * matrix.m[0][2] * matrix.m[3][1] -
//                      matrix.m[3][0] * matrix.m[0][1] * matrix.m[1][2] +
//                      matrix.m[3][0] * matrix.m[0][2] * matrix.m[1][1];

//     result.m[3][3] = matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] -
//                      matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1] -
//                      matrix.m[1][0] * matrix.m[0][1] * matrix.m[2][2] +
//                      matrix.m[1][0] * matrix.m[0][2] * matrix.m[2][1] +
//                      matrix.m[2][0] * matrix.m[0][1] * matrix.m[1][2] -
//                      matrix.m[2][0] * matrix.m[0][2] * matrix.m[1][1];

//     det = matrix.m[0][0] * result.m[0][0] +
//           matrix.m[0][1] * result.m[1][0] +
//           matrix.m[0][2] * result.m[2][0] +
//           matrix.m[0][3] * result.m[3][0];

//     if (det == 0.0f) {
//         printf("Matrix is not invertible\n");
//         return matrix;
//     }

//     det = 1.0f / det;

//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < 4; j++) {
//             result.m[i][j] *= det;
//         }
//     }

//     return result;
// }

// t_mat4 inverse_mat4(t_mat4 matrix)
// {
// 	t_mat4 result;
// 	int i, j, k;
// 	float temp, pivot;

// 	// printf("Determinant: %f\n", determinant(matrix));
// 	// if (determinant(matrix) == 0.0f) {
// 	// 	return matrix;
// 	// }

// 	// Initialize the result matrix as the identity matrix
// 	for (i = 0; i < 3; i++) {
// 		for (j = 0; j < 3; j++) {
// 			result.m[i][j] = (i == j) ? 1.0f : 0.0f;
// 		}
// 	}

// 	// Perform Gauss-Jordan elimination with partial pivoting
// 	for (i = 0; i < 4; i++) {
// 		// Find the row with the largest pivot
// 		pivot = matrix.m[i][i];
// 		int pivotRow = i;
// 		for (j = i + 1; j < 4; j++) {
// 			if (matrix.m[j][i] > pivot) {
// 				pivot = matrix.m[j][i];
// 				pivotRow = j;
// 			}
// 		}

// 		// Swap rows if necessary
// 		if (pivotRow != i) {
// 			for (j = 0; j < 4; j++) {
// 				// Swap matrix.m elements
// 				temp = matrix.m[i][j];
// 				matrix.m[i][j] = matrix.m[pivotRow][j];
// 				matrix.m[pivotRow][j] = temp;

// 				// Swap result elements
// 				temp = result.m[i][j];
// 				result.m[i][j] = result.m[pivotRow][j];
// 				result.m[pivotRow][j] = temp;
// 			}
// 		}

// 		// Divide the pivot row by the pivot value
// 		temp = matrix.m[i][i];
// 		for (j = 0; j < 4; j++) {
// 			matrix.m[i][j] /= temp;
// 			result.m[i][j] /= temp;
// 		}

// 		// Subtract multiples of the pivot row from other rows
// 		for (k = 0; k < 4; k++) {
// 			if (k != i) {
// 				temp = matrix.m[k][i];
// 				for (j = 0; j < 4; j++) {
// 					matrix.m[k][j] -= temp * matrix.m[i][j];
// 					result.m[k][j] -= temp * result.m[i][j];
// 				}
// 			}
// 		}
// 	}
// 	return result;
// }

void swap_float(float *a, float *b)
{
	float temp = *a;
	*a = *b;
	*b = temp;
}

// t_mat4 inverse_mat4(t_mat4 matrix)
// {
// 	// t_mat4 res = mat4_identity();
// 	// t_mat4 res = matrix;
// 	// matrix = mat4_identity();

// 	// //! subtract the first row from the second row
// 	// res.m[1][0] -= matrix.m[0][0];
// 	// res.m[1][1] -= matrix.m[0][1];
// 	// res.m[1][2] -= matrix.m[0][2];
// 	// res.m[1][3] -= matrix.m[0][3];
// 	// //! subtract the first row from the third row
// 	// res.m[2][0] -= matrix.m[0][0];
// 	// res.m[2][1] -= matrix.m[0][1];
// 	// res.m[2][2] -= matrix.m[0][2];
// 	// res.m[2][3] -= matrix.m[0][3];
// 	// //! add the first row to the fourth row
// 	// res.m[3][0] += matrix.m[0][0];
// 	// res.m[3][1] += matrix.m[0][1];
// 	// res.m[3][2] += matrix.m[0][2];
// 	// res.m[3][3] += matrix.m[0][3];
// 	// //! switch the second and forth row
// 	// swap_float(&res.m[1][0], &res.m[3][0]);
// 	// swap_float(&res.m[1][1], &res.m[3][1]);
// 	// swap_float(&res.m[1][2], &res.m[3][2]);
// 	// swap_float(&res.m[1][3], &res.m[3][3]);
// 	// //! multiplay the second row by 1/2
// 	// res.m[1][0] *= 0.5f;
// 	// res.m[1][1] *= 0.5f;
// 	// res.m[1][2] *= 0.5f;
// 	// res.m[1][3] *= 0.5f;
// 	// //! subtract the second row from the first row
// 	// res.m[0][0] -= matrix.m[1][0];
// 	// res.m[0][1] -= matrix.m[1][1];
// 	// res.m[0][2] -= matrix.m[1][2];
// 	// res.m[0][3] -= matrix.m[1][3];
// 	// //! add 2 times the second row to the third row
// 	// res.m[2][0] += (2 * matrix.m[1][0]);
// 	// res.m[2][1] += (2 * matrix.m[1][1]);
// 	// res.m[2][2] += (2 * matrix.m[1][2]);
// 	// res.m[2][3] += (2 * matrix.m[1][3]);
// 	// //! multiplay the thrird row by 1/2
// 	// res.m[2][0] *= 0.5f;
// 	// res.m[2][1] *= 0.5f;
// 	// res.m[2][2] *= 0.5f;
// 	// res.m[2][3] *= 0.5f;
// 	// //! subtract the third row from the second row
// 	// res.m[1][0] -= matrix.m[2][0];
// 	// res.m[1][1] -= matrix.m[2][1];
// 	// res.m[1][2] -= matrix.m[2][2];
// 	// res.m[1][3] -= matrix.m[2][3];
// 	// //! add 2 times the thrird row to the fourth row
// 	// res.m[3][0] += (2 * matrix.m[2][0]);
// 	// res.m[3][1] += (2 * matrix.m[2][1]);
// 	// res.m[3][2] += (2 * matrix.m[2][2]);
// 	// res.m[3][3] += (2 * matrix.m[2][3]);
// 	// //! multiplay the fourth row by 1/4
// 	// res.m[3][0] *= 0.25f;
// 	// res.m[3][1] *= 0.25f;
// 	// res.m[3][2] *= 0.25f;
// 	// res.m[3][3] *= 0.25f;
// 	// //! add the fourth row to the first row
// 	// res.m[0][0] += matrix.m[3][0];
// 	// res.m[0][1] += matrix.m[3][1];
// 	// res.m[0][2] += matrix.m[3][2];
// 	// res.m[0][3] += matrix.m[3][3];
// 	// //! add the fourth row to the second row
// 	// res.m[1][0] += matrix.m[3][0];
// 	// res.m[1][1] += matrix.m[3][1];
// 	// res.m[1][2] += matrix.m[3][2];
// 	// res.m[1][3] += matrix.m[3][3];
// 	// //! subtract the fourth row from the third row
// 	// res.m[2][0] -= matrix.m[3][0];
// 	// res.m[2][1] -= matrix.m[3][1];
// 	// res.m[2][2] -= matrix.m[3][2];
// 	// res.m[2][3] -= matrix.m[3][3];


// 	// t_mat4 res = matrix;
// 	// matrix = mat4_identity();
// 	//! subtract the first row from the second row
// 	matrix.m[1][0] -= matrix.m[0][0];
// 	matrix.m[1][1] -= matrix.m[0][1];
// 	matrix.m[1][2] -= matrix.m[0][2];
// 	matrix.m[1][3] -= matrix.m[0][3];
// 	//! subtract the first row from the third row
// 	matrix.m[2][0] -= matrix.m[0][0];
// 	matrix.m[2][1] -= matrix.m[0][1];
// 	matrix.m[2][2] -= matrix.m[0][2];
// 	matrix.m[2][3] -= matrix.m[0][3];
// 	//! add the first row to the fourth row
// 	matrix.m[3][0] += matrix.m[0][0];
// 	matrix.m[3][1] += matrix.m[0][1];
// 	matrix.m[3][2] += matrix.m[0][2];
// 	matrix.m[3][3] += matrix.m[0][3];
// 	//! switch the second and forth row
// 	swap_float(&matrix.m[1][0], &matrix.m[3][0]);
// 	swap_float(&matrix.m[1][1], &matrix.m[3][1]);
// 	swap_float(&matrix.m[1][2], &matrix.m[3][2]);
// 	swap_float(&matrix.m[1][3], &matrix.m[3][3]);
// 	//! multiplay the second row by 1/2
// 	matrix.m[1][0] *= 0.5f;
// 	matrix.m[1][1] *= 0.5f;
// 	matrix.m[1][2] *= 0.5f;
// 	matrix.m[1][3] *= 0.5f;
// 	//! subtract the second row from the first row
// 	matrix.m[0][0] -= matrix.m[1][0];
// 	matrix.m[0][1] -= matrix.m[1][1];
// 	matrix.m[0][2] -= matrix.m[1][2];
// 	matrix.m[0][3] -= matrix.m[1][3];
// 	//! add 2 times the second row to the third row
// 	matrix.m[2][0] += (2 * matrix.m[1][0]);
// 	matrix.m[2][1] += (2 * matrix.m[1][1]);
// 	matrix.m[2][2] += (2 * matrix.m[1][2]);
// 	matrix.m[2][3] += (2 * matrix.m[1][3]);
// 	//! multiplay the thrird row by 1/2
// 	matrix.m[2][0] *= 0.5f;
// 	matrix.m[2][1] *= 0.5f;
// 	matrix.m[2][2] *= 0.5f;
// 	matrix.m[2][3] *= 0.5f;
// 	//! subtract the third row from the second row
// 	matrix.m[1][0] -= matrix.m[2][0];
// 	matrix.m[1][1] -= matrix.m[2][1];
// 	matrix.m[1][2] -= matrix.m[2][2];
// 	matrix.m[1][3] -= matrix.m[2][3];
// 	//! add 2 times the thrird row to the fourth row
// 	matrix.m[3][0] += (2 * matrix.m[2][0]);
// 	matrix.m[3][1] += (2 * matrix.m[2][1]);
// 	matrix.m[3][2] += (2 * matrix.m[2][2]);
// 	matrix.m[3][3] += (2 * matrix.m[2][3]);
// 	//! multiplay the fourth row by 1/4
// 	matrix.m[3][0] *= 0.25f;
// 	matrix.m[3][1] *= 0.25f;
// 	matrix.m[3][2] *= 0.25f;
// 	matrix.m[3][3] *= 0.25f;
// 	//! add the fourth row to the first row
// 	matrix.m[0][0] += matrix.m[3][0];
// 	matrix.m[0][1] += matrix.m[3][1];
// 	matrix.m[0][2] += matrix.m[3][2];
// 	matrix.m[0][3] += matrix.m[3][3];
// 	//! add the fourth row to the second row
// 	matrix.m[1][0] += matrix.m[3][0];
// 	matrix.m[1][1] += matrix.m[3][1];
// 	matrix.m[1][2] += matrix.m[3][2];
// 	matrix.m[1][3] += matrix.m[3][3];
// 	//! subtract the fourth row from the third row
// 	matrix.m[2][0] -= matrix.m[3][0];
// 	matrix.m[2][1] -= matrix.m[3][1];
// 	matrix.m[2][2] -= matrix.m[3][2];
// 	matrix.m[2][3] -= matrix.m[3][3];

// 	return matrix;
// }


t_mat4 swap_rows(t_mat4 mat, int row1, int row2) {
    for (int i = 0; i < 4; i++) {
        float temp = mat.m[row1][i];
        mat.m[row1][i] = mat.m[row2][i];
        mat.m[row2][i] = temp;
    }
	return mat;
}

t_mat4 scale_row(t_mat4 mat, int row, float scalar) {
    for (int i = 0; i < 4; i++) {
        mat.m[row][i] *= scalar;
    }
	return mat;
}

t_mat4 add_rows(t_mat4 mat, int row1, int row2, float scalar) {
    for (int i = 0; i < 4; i++) {
        mat.m[row1][i] += scalar * mat.m[row2][i];
    }
	return mat;
}

void identity_matrix(t_mat4 mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j)
                mat.m[i][j] = 1.0;
            else
                mat.m[i][j] = 0.0;
        }
    }
}

t_mat4 inverse_mat4 (t_mat4 m) {
	t_mat4 inv = mat4_identity();
	t_mat4 mat = m;
	for (int i = 0; i < 4; i++) {

		// Find pivot
		int pivot_row = i;
		float pivot = mat.m[i][i];

		for (int j = i + 1; j < 4; j++) {
			if (fabs(mat.m[j][i]) > fabs(pivot)) {
				pivot_row = j;
				pivot = mat.m[j][i];
			}
		}

		// t_mat4 is singular (no inverse)
		if (fabs(pivot) < 1e-8) {
			return mat;
		}

		// Swap pivot row with current row
		mat = swap_rows(mat, i, pivot_row);
		inv = swap_rows(inv, i, pivot_row);

		// Scale pivot row
		mat = scale_row(mat, i, 1.0f / pivot);
		inv = scale_row(inv, i, 1.0f / pivot);

		// Eliminate other rows
		for (int j = 0; j < 4; j++) {
			if (j != i) {
				float factor = -mat.m[j][i];
				mat = add_rows(mat, j, i, factor);
				inv = add_rows(inv, j, i, factor);
			}
		}
	}
	return inv;
}







void print_matrix(t_mat4 matrix)
{
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			printf("%7.2f", matrix.m[i][j]);
		}
		printf("\n");
	}
}













#include <math.h>

t_mat4 perspective(float fov, float width, float height, float nearclip, float farclip) {
	float aspectRatio = width / height;
	float tanHalfFov = tanf(fov / 2.0f);
	t_mat4 res;
		
	res.m[0][0] = 1.0f / (aspectRatio * tanHalfFov);
	res.m[0][1] = 0.0f;
	res.m[0][2] = 0.0f;
	res.m[0][3] = 0.0f;
		
	res.m[1][0] = 0.0f;
	res.m[1][1] = 1.0f / tanHalfFov;
	res.m[1][2] = 0.0f;
	res.m[1][3] = 0.0f;
		
	res.m[2][0] = 0.0f;
	res.m[2][1] = 0.0f;
	res.m[2][2] = -(farclip + nearclip) / (farclip - nearclip);
	res.m[2][3] = -1.0f;
		
	res.m[3][0] = 0.0f;
	res.m[3][1] = 0.0f;
	res.m[3][2] = -(2.0f * farclip * nearclip) / (farclip - nearclip);
	res.m[3][3] = 0.0f;

	return res;
}





t_vec4 mat4_mul_vec4(t_mat4 m, t_vec4 v) {
	t_vec4 res;
	res.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[3][0] * v.w;
	res.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z + m.m[3][1] * v.w;
	res.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z + m.m[3][2] * v.w;
	res.w = m.m[0][3] * v.x + m.m[1][3] * v.y + m.m[2][3] * v.z + m.m[3][3] * v.w;
	return res;
}