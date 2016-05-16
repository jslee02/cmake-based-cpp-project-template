#ifndef _DART_COMMAND_H_
#define _DART_COMMAND_H_

#include <string>
#include <vector>
#include <exception>

#include "dart/common/Types.h"
#include "dart/common/Enums.h"

namespace dart {

/// class Command
class Command
{
public:
  /// Destructor
  virtual ~Command();

  /// Excute
  virtual XError execute() = 0;

  /// Undo
  virtual XError undo() = 0;

  /// Return the description
  virtual const std::string& getDescription();

  ///
  DWORD getSeqNum() const;

protected:
  /// Constructor
  Command();

protected:
  /// Description
  std::string mDescription;

  ///
  bool m_bFirstExecuted;

  ///
  DWORD m_dwSeqNum;
};

/// class MacroCommand
class MacroCommand : public Command
{
public:
  /// Constructor
  MacroCommand();

  /// Constructor
  explicit MacroCommand(const std::vector<Command*>& _commands);

  /// Destructor
  virtual ~MacroCommand();

  /// Push a command
  void push(Command* _command);

  /// Pop a command
  Command* pop();

  /// Return the number of commands
  int getCount() const;

public:
  //----------------------------------------------------------------------------
  // Command virtual functions
  //----------------------------------------------------------------------------

  // Documentation inherited
  virtual std::string& getDescription();

  // Documentation inherited
  virtual XError execute();

  // Documentation inherited
  virtual XError undo();

protected:

  /// Commands
  std::vector<Command*> mCommands;
};

}

#endif  // _DART_COMMAND_H_
