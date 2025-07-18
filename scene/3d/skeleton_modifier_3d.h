/**************************************************************************/
/*  skeleton_modifier_3d.h                                                */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#pragma once

#include "scene/3d/node_3d.h"

#include "scene/3d/skeleton_3d.h"

class SkeletonModifier3D : public Node3D {
	GDCLASS(SkeletonModifier3D, Node3D);

	void rebind();

public:
	enum BoneAxis {
		BONE_AXIS_PLUS_X,
		BONE_AXIS_MINUS_X,
		BONE_AXIS_PLUS_Y,
		BONE_AXIS_MINUS_Y,
		BONE_AXIS_PLUS_Z,
		BONE_AXIS_MINUS_Z,
	};

protected:
	bool active = true;
	real_t influence = 1.0;

	// Cache them for the performance reason since finding node with NodePath is slow.
	ObjectID skeleton_id;

	void _update_skeleton();
	void _update_skeleton_path();
	void _force_update_skeleton_skin();

	virtual void _skeleton_changed(Skeleton3D *p_old, Skeleton3D *p_new);
	virtual void _validate_bone_names();
	GDVIRTUAL2(_skeleton_changed, Skeleton3D *, Skeleton3D *);
	GDVIRTUAL0(_validate_bone_names);

	void _notification(int p_what);
	static void _bind_methods();

	virtual void _set_active(bool p_active);

	virtual void _process_modification(double p_delta);
	// TODO: In Godot 5, should obsolete old GDVIRTUAL0(_process_modification); and replace it with _process_modification_with_delta as GDVIRTUAL1(_process_modification, double).
	GDVIRTUAL1(_process_modification_with_delta, double);
#ifndef DISABLE_DEPRECATED
	GDVIRTUAL0(_process_modification);
#endif

public:
	virtual PackedStringArray get_configuration_warnings() const override;
	virtual bool has_process() const { return false; } // Return true if modifier needs to modify bone pose without external animation such as physics, jiggle and etc.

	void set_active(bool p_active);
	bool is_active() const;

	void set_influence(real_t p_influence);
	real_t get_influence() const;

	Skeleton3D *get_skeleton() const;

	void process_modification(double p_delta);

	// Utility APIs.
	static Vector3 get_vector_from_bone_axis(BoneAxis p_axis);
	static Vector3 get_vector_from_axis(Vector3::Axis p_axis);
	static Vector3::Axis get_axis_from_bone_axis(BoneAxis p_axis);

	static Vector3 limit_length(const Vector3 &p_origin, const Vector3 &p_destination, float p_length);
	static Quaternion get_local_pose_rotation(Skeleton3D *p_skeleton, int p_bone, const Quaternion &p_global_pose_rotation);
	static Quaternion get_from_to_rotation(const Vector3 &p_from, const Vector3 &p_to, const Quaternion &p_prev_rot);
	static Vector3 snap_vector_to_plane(const Vector3 &p_plane_normal, const Vector3 &p_vector);

#ifdef TOOLS_ENABLED
	virtual bool is_processed_on_saving() const { return false; }
#endif

	SkeletonModifier3D();
};

VARIANT_ENUM_CAST(SkeletonModifier3D::BoneAxis);
