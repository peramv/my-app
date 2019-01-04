﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_different_record_length : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_different_record_length() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_different_record_length() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_DIFFERENT_RECORD_LENGTH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Distribution record is currently locked by another user, please try again.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Distribution record is currently locked by another user, please try again.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verteilungseintrag ist zur Zeit durch einen anderen Benutzer gesperrt, bitte versuchen Sie es später erneut.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro de distribución está actualmente bloqueado por otro usuario, por favor vuelva a intentarlo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de distribution est actuellement verrouillé par un autre utilisateur. Veuillez réessayer.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Distributierecord is op dit moment vergrendeld door een andere gebruiker, probeer het nog eens")); }

        // Actions
	};
}



