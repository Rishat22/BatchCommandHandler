#include "shape_command.h"

ShapeCommand::ShapeCommand(const std::shared_ptr<GraphicsController>& controller)
	: m_controller(controller)
{
}

AddShapeCommand::AddShapeCommand(const std::shared_ptr<GraphicsController>& controller, const std::shared_ptr<GraphicsShape>& shape)
	: ShapeCommand(controller)
	, m_shape(shape)
{
}

void AddShapeCommand::execute()
{
	m_controller->addShape(m_shape);
}

RemoveShapeCommand::RemoveShapeCommand(const std::shared_ptr<GraphicsController>& controller, const std::shared_ptr<GraphicsShape>& shape)
	: ShapeCommand(controller)
	, m_shape(shape)
{
}

void RemoveShapeCommand::execute()
{
	m_controller->removeShape(m_shape);
}
