﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_audit_rec_not_written : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_audit_rec_not_written() { }
		~CBase_Ifds_dita2kdb_dita2kdb_audit_rec_not_written() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_AUDIT_REC_NOT_WRITTEN")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An error occured while attempting to connect to host using VM connection.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Schwebender Handel nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("An error occured while attempting to connect to host using VM connection.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une erreur s'est produite lors de la tentative de connexion à l'hôte en utilisant une connection au gestionnaire de l'affichage.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("An error occured while attempting to connect to host using VM connection.")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("NULL")); }
	};
}



