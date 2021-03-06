/**
 * This file is part of the "plotfx" project
 *   Copyright (c) 2018 Paul Asmuth
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "geometry.h"

namespace plotfx {

enum class HAlign {
  LEFT, CENTER, RIGHT
};

enum class VAlign {
  TOP, CENTER, BOTTOM
};

enum class Direction {
  HORIZONTAL, VERTICAL
};

Rectangle layout_margin_box(
    const Rectangle& parent,
    double margin_top,
    double margin_right,
    double margin_bottom,
    double margin_left);

/**
 * Given a bounding box and a target point (tx, ty) and (sx, sy) == (0, 0),
 * calculate a translate offset (ox, oy) for the bounding box so that new
 * bounding box midpoint point is equal to the target point.
 */
Point layout_align(
    const Rectangle& bbox,
    const Point& target);

/**
 * Given a bounding box and a target point (tx, ty) and (sx, sy) == (0, 0),
 * calculate a translate offset (ox, oy) for the bounding box so that new
 * bounding box alignment point is equal to the target point. You can choose
 * from one of 9 alignment points using the halign and valign parameters.
 */
Point layout_align(
    const Rectangle& bbox,
    Point target,
    HAlign halign,
    VAlign valign);


} // namespace plotfx

