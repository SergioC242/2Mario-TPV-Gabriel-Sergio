#include "SceneObject.h"

void SceneObject::setListAnchor(GameList<SceneObject>::anchor&& anchor) {
	this->anchor = std::move(anchor);
}