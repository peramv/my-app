#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_data_set_id_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_data_set_id_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_data_set_id_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_DATA_SET_ID_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one entity must be set up to continue.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Au moins une entite doit être definie pour continuer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mindestens ein Objekt muss erstellt werden, um fortfahren zu können.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse al menos una entidad para continuar.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous devez régler au moins une entité pour continuer.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet ten minste één eenheid worden ingesteld om door te gaan")); }

        // Actions
	};
}



