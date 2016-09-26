#include "UIElement.h"



UIElement::UIElement(){

	topLeft = Vector2f(-60 * SCALEFACTOR / 64, 60 * SCALEFACTOR / 64);
	botRight = Vector2f(-40 * SCALEFACTOR / 64, 40 * SCALEFACTOR / 64);
	isVisible = true;

}


UIElement::~UIElement()
{
}

void UIElement::draw()
{
	if (isVisible) {
		ShaderProgram * shader = Res::getShader(uiShader);
		shader->loadVector2f("scale", -1 * topLeft + botRight);
		shader->loadVector2f("pos", topLeft);

		Res::stdModel->bind();
		glDrawArrays(GL_TRIANGLES, 0, Res::stdModel->numberOfVertices);

	}
}
