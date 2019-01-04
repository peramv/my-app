﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_taf_not_equal_master : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_taf_not_equal_master() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_taf_not_equal_master() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_TAF_NOT_EQUAL_MASTER")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("TAF not equal master.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("TAF not equal master.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("TAF nicht gleich Master.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El TAF no coincide con el maestro.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le TAF n'est pas identique à l'original.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("TAF is niet gelijk aan hoofdrecord")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



