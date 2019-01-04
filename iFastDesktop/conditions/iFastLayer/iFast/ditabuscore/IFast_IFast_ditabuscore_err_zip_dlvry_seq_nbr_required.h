﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_zip_dlvry_seq_nbr_required : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_zip_dlvry_seq_nbr_required() { }
		~CIFast_IFast_ditabuscore_err_zip_dlvry_seq_nbr_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ZIP_DLVRY_SEQ_NBR_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Address code is used by mailing assignments, can not be deleted.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le code d'adresse est utilise pour les affectations de mailing, impossible de le supprimer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Adresscode wird von Mailing-Zuweisungen verwendet, er kann nicht gelöscht werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de dirección es utilizado para envíos de correspondencia, no puede eliminarse.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code d'adresse est utilisé à des fins de diffusion et ne peut être supprimé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Adrescode wordt gebruikt door mailingopdrachten, kan niet worden gewist")); }

        // Actions
	};
}



