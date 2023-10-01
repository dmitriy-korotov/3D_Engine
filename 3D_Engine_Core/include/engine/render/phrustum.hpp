#pragma once



namespace engine::render
{
	struct orthographic_frustum
	{
		float right_plane = 2.f;
		float top_plane = 2.f;	
		float far_plane = 100.f;
		float near_plane = 0.1f;
	};

	struct prespective_frustum
	{
		float near_plane = 0.1f;
		float far_plane = 100.f;
		float field_of_view = 60.f;
	};
}