#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_zip_dlvry_seq_nbr_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_zip_dlvry_seq_nbr_not_allowed() { }
		~CIFast_IFast_ditabuscore_err_zip_dlvry_seq_nbr_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ZIP_DLVRY_SEQ_NBR_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No branches for the broker %broker%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucune succursale pour le courtier %broker%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Filialen für den Broker %broker%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay sucursales para el corredor %broker%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune unité de service pour le courtier %broker%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen filialen voor makelaar %broker%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Select another broker.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Selectionnez un autre courtier.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wählen Sie einen anderen Broker aus.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Select another broker.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Sélectionnez un autre courtier.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Selecteer een andere makelaar")); }
	};
}



