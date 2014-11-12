#include "Command.h"

#include <cassert>
#include <sstream>

namespace dart {

//==============================================================================
Command::Command()
{
  static DWORD dwSeed = 0;

  m_dwSeqNum = ++dwSeed;
  m_bFirstExecuted = true;
  mDescription = "Unnamed Command";
}

//==============================================================================
Command::~Command()
{
}

//==============================================================================
const std::string& Command::getDescription()
{
  return mDescription;
}

//==============================================================================
DWORD Command::getSeqNum() const
{
  return m_dwSeqNum;
}

//==============================================================================
MacroCommand::MacroCommand()
  : Command()
{

}

//==============================================================================
MacroCommand::MacroCommand(const std::vector<Command*>& _commands)
  : Command()
{
  mCommands = _commands;
}

//==============================================================================
MacroCommand::~MacroCommand()
{
  for (std::vector<Command*>::reverse_iterator ri = mCommands.rbegin();
       ri != mCommands.rend(); ++ri)
  {
    delete (*ri);
  }

  mCommands.clear();
}

//==============================================================================
void MacroCommand::push(Command* _command)
{
  mCommands.push_back(_command);
}

//==============================================================================
Command* MacroCommand::pop()
{
  if (mCommands.empty())
  {
    return nullptr;
  }
  else
  {
    Command* pCmd = mCommands.back();
    mCommands.pop_back();
    return pCmd;
  }
}

//==============================================================================
int MacroCommand::getCount() const
{
  assert((int)mCommands.size() >= 0);

  return (int)mCommands.size();
}

//==============================================================================
std::string& MacroCommand::getDescription()
{
  std::stringstream ss;
  ss << mCommands.size() << " commands";
  mDescription = ss.str();

  return mDescription;
}

//==============================================================================
XError MacroCommand::execute()
{
  assert((int)mCommands.size() >= 0);

  for (std::vector<Command*>::iterator i = mCommands.begin();
       i != mCommands.end(); ++i)
  {
    XError eResult = (*i)->execute();

    if (eResult != XError::Success)
    {
      for (; i == mCommands.begin(); --i)
        (*i)->undo();

      return XError::TransactionFailed;
    }
  }

  return XError::Success;
}

//==============================================================================
XError MacroCommand::undo()
{
  for (std::vector<Command*>::reverse_iterator i = mCommands.rbegin();
       i != mCommands.rend(); ++i)
  {
    XError eResult = (*i)->undo();

    if (eResult != XError::Success)
    {
      for (; i == mCommands.rbegin(); --i)
        (*i)->execute();

      return XError::TransactionFailed;
    }
  }

  return XError::Success;
}

}  // namespace dart

