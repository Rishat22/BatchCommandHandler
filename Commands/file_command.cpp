#include "file_command.h"


FileCommand::FileCommand(const std::shared_ptr<GraphicsModel>& model)
	: m_model(model)
{
}

LoadFileCommand::LoadFileCommand(const std::shared_ptr<GraphicsModel>& model, const std::string& fname)
	: FileCommand(model)
	, m_fname(fname)
{
}

void LoadFileCommand::execute()
{
	m_model->loadFile(m_fname);
}

SaveAsCommand::SaveAsCommand(const std::shared_ptr<GraphicsModel>& model, const std::string& fname)
	: FileCommand(model)
	, m_fname(fname)
{
}

void SaveAsCommand::execute()
{
	m_model->saveFile(m_fname);
}
