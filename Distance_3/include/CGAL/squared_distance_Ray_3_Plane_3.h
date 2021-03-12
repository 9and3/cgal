// Copyright (c) 1998-2021
// Utrecht University (The Netherlands),
// ETH Zurich (Switzerland),
// INRIA Sophia-Antipolis (France),
// Max-Planck-Institute Saarbruecken (Germany),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org)
//
// $URL$
// $Id$
// SPDX-License-Identifier: LGPL-3.0-or-later OR LicenseRef-Commercial
//
//
// Author(s)     : Geert-Jan Giezeman, Andreas Fabri

#ifndef CGAL_DISTANCE_3_RAY_3_PLANE_3_H
#define CGAL_DISTANCE_3_RAY_3_PLANE_3_H

#include <CGAL/internal/squared_distance_utils_3.h>

#include <CGAL/Plane_3.h>
#include <CGAL/Ray_3.h>
#include <CGAL/number_utils.h>

namespace CGAL {
namespace internal {

template <class K>
typename K::FT
squared_distance(const typename K::Ray_3 &ray,
                 const typename K::Plane_3 &plane,
                 const K& k)
{
  typedef typename K::Point_3 Point_3;
  typedef typename K::Vector_3 Vector_3;
  typedef typename K::RT RT;
  typedef typename K::FT FT;

  typename K::Construct_vector_3 construct_vector;

  const Point_3 &start = ray.start();
  const Point_3 &planepoint = plane.point();
  Vector_3 start_min_pp = construct_vector(planepoint, start);
  Vector_3 end_min_pp = ray.direction().vector();
  const Vector_3 &normal = plane.orthogonal_vector();
  RT sdm_rs2pp = wdot(normal, start_min_pp, k);
  RT sdm_re2pp = wdot(normal, end_min_pp, k);

  switch (CGAL_NTS sign(sdm_rs2pp))
  {
    case -1:
      if (sdm_re2pp > RT(0))
        return FT(0);
      return squared_distance_to_plane(normal, start_min_pp, k);
    case 0:
    default:
      return FT(0);
    case 1:
      if (sdm_re2pp < RT(0))
        return FT(0);
      return squared_distance_to_plane(normal, start_min_pp, k);
  }
}

template <class K>
inline typename K::FT
squared_distance(const typename K::Plane_3& plane,
                 const typename K::Ray_3& ray,
                 const K& k)
{
  return squared_distance(ray, plane, k);
}

} // namespace internal

template <class K>
inline
typename K::FT
squared_distance(const Ray_3<K>& ray,
                 const Plane_3<K>& plane)
{
  return internal::squared_distance(ray, plane, K());
}

template <class K>
inline
typename K::FT
squared_distance(const Plane_3<K>& plane,
                 const Ray_3<K>& ray)
{
  return internal::squared_distance(ray, plane, K());
}

} // namespace CGAL

#endif // CGAL_DISTANCE_3_RAY_3_PLANE_3_H
