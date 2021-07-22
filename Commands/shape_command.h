#ifndef SHAPECOMMAND_H
#define SHAPECOMMAND_H
#include "icommand.h"

class ShapeCommand : public ICommand
{
public:
	virtual ~ShapeCommand() = default;
protected:
	ShapeCommand(const std::shared_ptr<GraphicsController>& controller);
protected:
	std::shared_ptr<GraphicsController> m_controller;
};

class AddShapeCommand : public ShapeCommand
{
public:
	AddShapeCommand(const std::shared_ptr<GraphicsController>& controller, const std::shared_ptr<GraphicsShape>& shape);
	virtual ~AddShapeCommand() = default;
	void execute() override;
private:
	std::shared_ptr<GraphicsShape> m_shape;
};

class RemoveShapeCommand : public ShapeCommand
{
public:
	RemoveShapeCommand(const std::shared_ptr<GraphicsController>& controller, const std::shared_ptr<GraphicsShape>& shape);
	virtual ~RemoveShapeCommand() = default;
	void execute() override;
private:
	std::shared_ptr<GraphicsShape> m_shape;
};

#endif // SHAPECOMMAND_H
