#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicore_dicore_oversize_buffer : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicore_dicore_oversize_buffer() { }
		~CBase_Infrastructure_dicore_dicore_oversize_buffer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_OVERSIZE_BUFFER")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%GENERIC%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%GENERIC%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check code using TransactPipeClient/TransactPipeServer.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check code using TransactPipeClient/TransactPipeServer.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Code mithilfe desTransactPipeClient/TransactPipeServers.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el código utilizando TransactPipeClient/TransactPipeServer.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code en utilisant le client du canal de transaction/serveur du canal de transaction.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de code die TransactPipeClient/TransactPipeServer gebruikt")); }
	};
}



