/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:21:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/20 00:05:38 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#define TINYEXR_IMPLEMENTATION
#include "./includes/tinyexr.h"
#include "./includes/miniz.h"


int main()
{
  const char* input = "asakusa.exr";
  float* out; // width * height * RGBA
  int width;
  int height;
  const char* err = NULL; // or nullptr in C++11

  int ret = LoadEXR(&out, &width, &height, input, &err);

  if (ret != TINYEXR_SUCCESS) {
    if (err) {
       fprintf(stderr, "ERR : %s\n", err);
       FreeEXRErrorMessage(err); // release memory of error message.
    }
  } else {
    free(out); // release memory of image data
  }
}
