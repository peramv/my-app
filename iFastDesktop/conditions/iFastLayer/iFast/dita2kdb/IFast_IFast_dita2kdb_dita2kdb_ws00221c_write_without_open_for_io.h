#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_write_without_open_for_io : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_write_without_open_for_io() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_write_without_open_for_io() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_WRITE_WITHOUT_OPEN_FOR_IO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pending record is currently locked by another user, please try again later.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Banking record is currently locked by another user, please try again later.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bevorstehender Eintrag ist zur Zeit durch einen anderen Benutzer gesperrt, bitte versuchen Sie es später erneut.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro pendiente está actualmente bloqueado por otro usuario, por favor vuelva a intentarlo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement en suspens est actuellement verrouillé par un autre utilisateur. Veuillez réessayer.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("In behandeling zijnde record is op dit moment vergrendeld door een andere gebruiker, probeer het later opnieuw")); }

        // Actions
	};
}



