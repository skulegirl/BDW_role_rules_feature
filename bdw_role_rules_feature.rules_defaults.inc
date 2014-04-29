<?php
/**
 * @file
 * bdw_role_rules_feature.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function bdw_role_rules_feature_default_rules_configuration() {
  $items = array();
  $items['rules_add_boondocking_available_flag_with_new_valid_bda_location'] = entity_import('rules_config', '{ "rules_add_boondocking_available_flag_with_new_valid_bda_location" : {
      "LABEL" : "add boondocking available flag with new valid BDA location ",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "flag_user" ],
      "REQUIRES" : [ "rules", "php", "flag", "profile2" ],
      "ON" : { "profile2_insert" : [] },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "profile2" ], "field" : "field_ba_bda_pref" } },
        { "data_is" : { "data" : [ "profile2:field-ba-bda-pref" ], "value" : 0 } },
        { "php_eval" : { "code" : "dd($profile2, \\u0027profile2\\u0027);\\r\\nreturn (location_has_coordinates($profile2-\\u003Efield_boondock_location[\\u0027und\\u0027][0]));" } }
      ],
      "DO" : [
        { "flag_flaguser" : {
            "flag" : "boondocking_available",
            "user" : [ "profile2:user" ],
            "flagging_user" : [ "profile2:user" ],
            "permission_check" : 1
          }
        }
      ]
    }
  }');
  $items['rules_add_boondocking_available_flag_with_valid_bda_location'] = entity_import('rules_config', '{ "rules_add_boondocking_available_flag_with_valid_bda_location" : {
      "LABEL" : "add boondocking available flag with valid BDA location",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "flag_user" ],
      "REQUIRES" : [ "rules", "php", "flag", "profile2" ],
      "ON" : { "profile2_update" : [] },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "profile2" ], "field" : "field_ba_bda_pref" } },
        { "data_is" : { "data" : [ "profile2:field-ba-bda-pref" ], "value" : 0 } },
        { "php_eval" : { "code" : "return (location_has_coordinates($profile2-\\u003Efield_boondock_location[\\u0027und\\u0027][0]));" } }
      ],
      "DO" : [
        { "flag_flaguser" : {
            "flag" : "boondocking_available",
            "user" : [ "profile2:user" ],
            "flagging_user" : [ "profile2:user" ],
            "permission_check" : 1
          }
        }
      ]
    }
  }');
  $items['rules_add_full_member_role_to_provisional_members_when_bda_flag_'] = entity_import('rules_config', '{ "rules_add_full_member_role_to_provisional_members_when_bda_flag_" : {
      "LABEL" : "Add full member role to provisional members when BDA flag is set",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules" ],
      "REQUIRES" : [ "rules", "mimemail", "flag" ],
      "ON" : { "flag_flagged_boondocking_available" : [] },
      "IF" : [
        { "user_has_role" : {
            "account" : [ "flagged-user" ],
            "roles" : { "value" : { "13" : "13" } }
          }
        }
      ],
      "DO" : [
        { "user_add_role" : { "account" : [ "flagged-user" ], "roles" : { "value" : { "8" : "8" } } } },
        { "drupal_message" : {
            "message" : "Thank you for adding a Boondocking Available location! You have now been promoted to a full member, and have full member privileges.",
            "repeat" : 0
          }
        },
        { "mimemail" : {
            "key" : "full member granted",
            "to" : [ "flagged-user:mail" ],
            "subject" : "You have been promoted to a full member!",
            "body" : "Dear [flagged-user:name],\\r\\n\\r\\nThank you for taking the time to enter a \\u0022Boondocking Available\\u0022 page with a location. Your generous offer to host other boondockers has now been made public, and your location will show up in searches on the site. \\r\\n\\r\\nNow that you have provided boondocking availability information, your membership is fully activated. This means that you now have the ability to send messages to other members, and create bookmarks for members who you might like to visit some day. Because of your membership requirements, should you ever remove your boondocking available location, your full-member privileges will be withdrawn until you either reinstate your boondocking availability or \\u003Ca href=\\u0022http:\\/\\/www.boondockerswelcome.com\\/membership-products\\/change-membership-type\\u0022\\u003Echange to an unrestricted membership\\u003C\\/a\\u003E.  See the \\u003Ca href=\\u0022http:\\/\\/www.boondockerswelcome.com\\/membership-products\\u0022\\u003Emembership products page\\u003C\\/a\\u003E for full details on all the different membership options.\\r\\n\\r\\nWelcome to the club, and happy boondocking!\\r\\n\\r\\nThe Boondockers Welcome Team",
            "plaintext" : "Dear [flagged-user:name],\\r\\n\\r\\nThank you for taking the time to enter a \\u0022Boondocking Available\\u0022 page with a location. Your generous offer to host other boondockers has now been made public, and your location will show up in searches on the site. \\r\\n\\r\\nNow that you have provided boondocking availability information, your membership is fully activated. This means that you now have the ability to send messages to other members, and create bookmarks for members who you might like to visit some day. Because of your membership requirements, should you ever remove your boondocking available location, your full-member privileges will be withdrawn until you either reinstate your boondocking availability or change to an unrestricted membership at http:\\/\\/www.boondockerswelcome.com\\/membership-products\\/change-membership-type.  See the membership products page at http:\\/\\/www.boondockerswelcome.com\\/membership-products for full details on all the different membership options.\\r\\n\\r\\nWelcome to the club, and happy boondocking!\\r\\n\\r\\nThe Boondockers Welcome Team",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_add_full_member_role_to_user_if_bda'] = entity_import('rules_config', '{ "rules_add_full_member_role_to_user_if_bda" : {
      "LABEL" : "Add \\u0022full member\\u0022 role to user if BDA",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "2",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "user_roles" ],
      "REQUIRES" : [ "rules", "flag", "uc_roles" ],
      "ON" : { "uc_roles_notify_grant" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "expiration:rid" ], "value" : "13" } },
        { "flag_flagged_user" : {
            "flag" : "boondocking_available",
            "user" : [ "order:customer" ],
            "flagging_user" : [ "order:customer" ]
          }
        }
      ],
      "DO" : [
        { "user_add_role" : {
            "account" : [ "order:customer" ],
            "roles" : { "value" : { "8" : "8" } }
          }
        }
      ]
    }
  }');
  $items['rules_add_membership_expired_role_to_user'] = entity_import('rules_config', '{ "rules_add_membership_expired_role_to_user" : {
      "LABEL" : "Add \\u0022membership expired\\u0022 role to user",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "user_roles" ],
      "REQUIRES" : [ "rules", "uc_roles" ],
      "ON" : { "uc_roles_notify_revoke" : [] },
      "IF" : [
        { "OR" : [
            { "data_is" : { "data" : [ "expiration:rid" ], "value" : "8" } },
            { "data_is" : { "data" : [ "expiration:rid" ], "value" : "13" } }
          ]
        }
      ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "18" : "18" } } } }
      ]
    }
  }');
  $items['rules_add_membership_expiring_flag_to_user'] = entity_import('rules_config', '{ "rules_add_membership_expiring_flag_to_user" : {
      "LABEL" : "Add \\u0022membership_expiring\\u0022 flag to user",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "flag_user" ],
      "REQUIRES" : [ "flag", "uc_roles" ],
      "ON" : { "uc_roles_notify_reminder" : [] },
      "DO" : [
        { "flag_flaguser" : {
            "flag" : "membership_expiring",
            "user" : [ "account" ],
            "flagging_user" : [ "account" ],
            "permission_check" : 0
          }
        }
      ]
    }
  }');
  $items['rules_add_purchased_membership_flag_and_role_to_user'] = entity_import('rules_config', '{ "rules_add_purchased_membership_flag_and_role_to_user" : {
      "LABEL" : "Add \\u0022purchased membership\\u0022 flag and role to user",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "2",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "flag_user" ],
      "REQUIRES" : [ "uc_order", "flag", "rules" ],
      "ON" : { "uc_order_status_update" : [] },
      "IF" : [
        { "uc_order_condition_has_product_class" : {
            "order" : [ "order" ],
            "product_classes" : { "value" : { "membership_level" : "membership_level" } },
            "required" : 0,
            "forbidden" : 0
          }
        },
        { "NOT uc_order_condition_order_state" : { "order" : [ "order" ], "order_state" : "completed" } },
        { "uc_order_condition_order_state" : { "order" : [ "updated-order" ], "order_state" : "completed" } }
      ],
      "DO" : [
        { "flag_flaguser" : {
            "flag" : "purchased_membership",
            "user" : [ "updated-order:customer" ],
            "flagging_user" : [ "updated-order:customer" ],
            "permission_check" : 0
          }
        },
        { "user_add_role" : {
            "account" : [ "updated-order:customer" ],
            "roles" : { "value" : { "20" : "20" } }
          }
        }
      ]
    }
  }');
  $items['rules_membership_expired_warning'] = entity_import('rules_config', '{ "rules_membership_expired_warning" : {
      "LABEL" : "Membership expired warning",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules" ],
      "REQUIRES" : [ "rules", "conditionalvariables" ],
      "ON" : { "init" : [] },
      "IF" : [
        { "user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "18" : "18" } }
          }
        },
        { "NOT conditionalvariables_page_condition" : { "pages" : "cart*\\r\\nmembership-products*" } }
      ],
      "DO" : [
        { "drupal_message" : {
            "message" : "Your account is currently EXPIRED. You cannot send messages to other members or access your bookmarks, and your available boondocking location, if entered, will not appear to others until you have \\u003Ca href=\\u0022\\/membership-products\\u0022\\u003Erenewed your membership\\u003C\\/a\\u003E.",
            "type" : "error",
            "repeat" : 0
          }
        }
      ]
    }
  }');
  $items['rules_membership_expiring_warning'] = entity_import('rules_config', '{ "rules_membership_expiring_warning" : {
      "LABEL" : "Membership expiring warning",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules" ],
      "REQUIRES" : [ "flag", "conditionalvariables", "rules", "php" ],
      "ON" : { "init" : [] },
      "IF" : [
        { "flag_flagged_user" : {
            "flag" : "membership_expiring",
            "user" : [ "site:current-user" ],
            "flagging_user" : [ "site:current-user" ]
          }
        },
        { "NOT conditionalvariables_page_condition" : { "pages" : "cart*\\r\\nmembership-products*" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "user", "value" : [ "site:current-user" ] },
            "PROVIDE" : { "variable_added" : { "current_user_var" : "current-user variable" } }
          }
        },
        { "drupal_message" : {
            "message" : "Your account is due to expire on \\u003C?php\\r\\n  $expiration = db_query(\\u0022SELECT expiration FROM {uc_roles_expirations} WHERE uid = :uid\\u0022, array(\\u0027:uid\\u0027 =\\u003E $current_user_var-\\u003Euid))-\\u003EfetchField();\\r\\n  echo format_date($expiration, \\u0027custom\\u0027, \\u0027l, F jS, Y\\u0027);\\r\\n  ?\\u003E. Please \\u003Ca href=\\u0022\\/membership-products\\u0022\\u003Erenew your membership\\u003C\\/a\\u003E to avoid a loss in membership privileges.",
            "type" : "warning",
            "repeat" : 0
          }
        }
      ]
    }
  }');
  $items['rules_not_full_member_warning'] = entity_import('rules_config', '{ "rules_not_full_member_warning" : {
      "LABEL" : "Not Full Member Warning",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules" ],
      "REQUIRES" : [ "rules", "conditionalvariables" ],
      "ON" : { "init" : [] },
      "IF" : [
        { "user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "13" : "13" } }
          }
        },
        { "NOT user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "8" : "8" } }
          }
        },
        { "NOT conditionalvariables_page_condition" : { "pages" : "membership-products*\\r\\ncart*\\r\\nuser\\/[site:current-user:uid]\\/edit*\\r\\nfilefield*" } }
      ],
      "DO" : [
        { "drupal_message" : {
            "message" : "WARNING! Your account does not currently have Full Member privileges. You need to either provide a \\u003Ca href=\\u0022\\/user\\/[site:current-user:uid]\\/edit\\/boondocking_available\\u0022\\u003E boondocking availabile location in your profile\\u003C\\/a\\u003E to meet the terms of your membership, or you need to \\u003Ca href=\\u0022\\/membership-products\\/change-membership-type\\u0022\\u003Echange your account to an unrestricted membership\\u003C\\/a\\u003E. Until this is resolved you cannot send messages to other members, or receive or give user recommendations, in addition to some other restrictions. Please resolve this quickly for your best Boondockers Welcome experience!",
            "type" : "warning",
            "repeat" : 0
          }
        }
      ]
    }
  }');
  $items['rules_redirect_to_account_info_on_first_login'] = entity_import('rules_config', '{ "rules_redirect_to_account_info_on_first_login" : {
      "LABEL" : "Redirect to account info on first login",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "BDW_misc_rules", "redirection" ],
      "REQUIRES" : [ "BDW_custom_changes", "rules" ],
      "ON" : { "user_login" : [] },
      "IF" : [ { "BDW_custom_changes_rules_condition_first_login" : [] } ],
      "DO" : [
        { "drupal_message" : {
            "message" : "Welcome to Boondockers Welcome! As your first order of business, please change your password to one of your choosing.",
            "repeat" : 0
          }
        },
        { "redirect" : { "url" : "user\\/[account:uid]\\/edit" } }
      ]
    }
  }');
  $items['rules_redirect_to_user_view_after_profile_saved'] = entity_import('rules_config', '{ "rules_redirect_to_user_view_after_profile_saved" : {
      "LABEL" : "Redirect to user view after profile saved",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "BDW_misc_rules", "redirection" ],
      "REQUIRES" : [ "rules", "profile2" ],
      "ON" : { "profile2_update" : [], "profile2_insert" : [] },
      "DO" : [
        { "redirect" : { "url" : "\\/users\\/[site:current-user:name]", "force" : 0 } }
      ]
    }
  }');
  $items['rules_remove_boondocking_available_flag_with_no_valid_bda_locati'] = entity_import('rules_config', '{ "rules_remove_boondocking_available_flag_with_no_valid_bda_locati" : {
      "LABEL" : "remove boondocking available flag with no valid BDA location",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "flag_user" ],
      "REQUIRES" : [ "rules", "php", "flag", "profile2" ],
      "ON" : { "profile2_update" : [] },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "profile2" ], "field" : "field_ba_bda_pref" } },
        { "OR" : [
            { "data_is" : { "data" : [ "profile2:field-ba-bda-pref" ], "value" : 1 } },
            { "php_eval" : { "code" : "return (!location_has_coordinates($profile2-\\u003Efield_boondock_location[\\u0027und\\u0027][0]));" } }
          ]
        }
      ],
      "DO" : [
        { "flag_unflaguser" : {
            "flag" : "boondocking_available",
            "user" : [ "profile2:user" ],
            "flagging_user" : [ "profile2:user" ],
            "permission_check" : 1
          }
        }
      ]
    }
  }');
  $items['rules_remove_expiring_membership_flag_from_user'] = entity_import('rules_config', '{ "rules_remove_expiring_membership_flag_from_user" : {
      "LABEL" : "Remove \\u0022membership_expiring\\u0022 flag from user",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "flag_user" ],
      "REQUIRES" : [ "rules", "flag", "uc_roles" ],
      "ON" : { "uc_roles_notify_revoke" : [] },
      "IF" : [
        { "OR" : [
            { "data_is" : { "data" : [ "expiration:rid" ], "value" : "8" } },
            { "data_is" : { "data" : [ "expiration:rid" ], "value" : "13" } }
          ]
        }
      ],
      "DO" : [
        { "flag_unflaguser" : {
            "flag" : "membership_expiring",
            "user" : [ "account" ],
            "flagging_user" : [ "account" ],
            "permission_check" : 0
          }
        }
      ]
    }
  }');
  $items['rules_remove_full_member_role_no_bda'] = entity_import('rules_config', '{ "rules_remove_full_member_role_no_bda" : {
      "LABEL" : "Remove full member role for provisional members when BDA flag is unest",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules" ],
      "REQUIRES" : [ "rules", "mimemail", "flag" ],
      "ON" : { "flag_unflagged_boondocking_available" : [] },
      "IF" : [
        { "user_has_role" : {
            "account" : [ "flagged-user" ],
            "roles" : { "value" : { "13" : "13" } }
          }
        }
      ],
      "DO" : [
        { "user_remove_role" : { "account" : [ "flagged-user" ], "roles" : { "value" : { "8" : "8" } } } },
        { "mimemail" : {
            "key" : "no longer full member email",
            "to" : [ "flagged-user:mail" ],
            "subject" : "WARNING! Full membership privileges have been revoked!",
            "body" : "Dear [flagged-user:name],\\r\\n\\r\\nYou recently removed your \\u0022Boondocking Available\\u0022 location from your Boondockers Welcome account. As a condition of your membership, you are required to provide a boondocking location in order to have full membership privileges. Please either re-instate your Boondocking Available location, or consider \\u003Ca href=\\u0022http:\\/\\/www.boondockerswelcome.com\\/membership-products\\/change-membership-type\\u0022\\u003Echanging to an unrestricted membership\\u003C\\/a\\u003E to regain your full member privileges. Only full members can send messages to other members, create bookmark lists of other members, and receive or leave user recommendations.\\r\\n\\r\\nRemember, when you provide a boondocking available location you are never under any obligation to host a fellow member, nor will they be able to determine your address from your location information. Your general location (either narrowed down by town\\/city or postal code if provided) will be shown on the search results map, and users will be able to send you messages through BoondockersWelcome.com, but your specific location or private contact information will never be made available to anyone.\\r\\n\\r\\nSincerely,\\r\\n\\r\\nThe Boondockers Welcome Team",
            "plaintext" : "Dear [flagged-user:name],\\r\\n\\r\\nYou recently removed your \\u0022Boondocking Available\\u0022 location from your Boondockers Welcome account. As a condition of your membership, you are required to provide a boondocking location in order to have full membership privileges. Please either re-instate your Boondocking Available location, or consider changing to an unrestricted membership (visit http:\\/\\/www.boondockerswelcome.com\\/membership-products\\/change-membership-type for details) to regain your full member privileges. Only full members can send messages to other members, create bookmark lists of other members, and receive or leave user recommendations.\\r\\n\\r\\nRemember, when you provide a boondocking available location you are never under any obligation to host a fellow member, nor will they be able to determine your address from your location information. Your general location (either narrowed down by town\\/city or postal code if provided) will be shown on the search results map, and users will be able to send you messages through BoondockersWelcome.com, but your specific location or private contact information will never be made available to anyone.\\r\\n\\r\\nSincerely,\\r\\n\\r\\nThe Boondockers Welcome Team",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_remove_full_member_role_when_bda_req_role_is_revoked'] = entity_import('rules_config', '{ "rules_remove_full_member_role_when_bda_req_role_is_revoked" : {
      "LABEL" : "Remove \\u0022full member\\u0022 role when BDA req role is revoked",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "1",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "user_roles" ],
      "REQUIRES" : [ "rules", "uc_roles" ],
      "ON" : { "uc_roles_notify_revoke" : [] },
      "IF" : [ { "data_is" : { "data" : [ "expiration:rid" ], "value" : "13" } } ],
      "DO" : [
        { "user_remove_role" : { "account" : [ "account" ], "roles" : { "value" : { "8" : "8" } } } }
      ]
    }
  }');
  $items['rules_remove_membership_expired_role_from_user'] = entity_import('rules_config', '{ "rules_remove_membership_expired_role_from_user" : {
      "LABEL" : "Remove \\u0022membership expired\\u0022 role from user",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "2",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "flag_user" ],
      "REQUIRES" : [ "uc_order", "rules" ],
      "ON" : { "uc_order_status_update" : [] },
      "IF" : [
        { "uc_order_condition_has_product_class" : {
            "order" : [ "order" ],
            "product_classes" : { "value" : { "membership_level" : "membership_level" } },
            "required" : 0,
            "forbidden" : 0
          }
        },
        { "NOT uc_order_condition_order_state" : { "order" : [ "order" ], "order_state" : "completed" } },
        { "uc_order_condition_order_state" : { "order" : [ "updated-order" ], "order_state" : "completed" } }
      ],
      "DO" : [
        { "user_remove_role" : {
            "account" : [ "updated-order:customer" ],
            "roles" : { "value" : { "18" : "18" } }
          }
        }
      ]
    }
  }');
  $items['rules_remove_membership_expiring_flag_from_user'] = entity_import('rules_config', '{ "rules_remove_membership_expiring_flag_from_user" : {
      "LABEL" : "Remove \\u0022membership_expiring\\u0022 flag from user",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "2",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "flag_user" ],
      "REQUIRES" : [ "uc_order", "flag" ],
      "ON" : { "uc_order_status_update" : [] },
      "IF" : [
        { "uc_order_condition_has_product_class" : {
            "order" : [ "order" ],
            "product_classes" : { "value" : { "membership_level" : "membership_level" } },
            "required" : 0,
            "forbidden" : 0
          }
        },
        { "NOT uc_order_condition_order_state" : { "order" : [ "order" ], "order_state" : "completed" } },
        { "uc_order_condition_order_state" : { "order" : [ "updated-order" ], "order_state" : "completed" } }
      ],
      "DO" : [
        { "flag_unflaguser" : {
            "flag" : "membership_expiring",
            "user" : [ "updated-order:customer" ],
            "flagging_user" : [ "updated-order:customer" ],
            "permission_check" : 0
          }
        }
      ]
    }
  }');
  $items['rules_transfer_bda_req_membership_to_full_member_role'] = entity_import('rules_config', '{ "rules_transfer_bda_req_membership_to_full_member_role" : {
      "LABEL" : "Transfer BDA req membership to full member role",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "user_roles" ],
      "REQUIRES" : [ "rules", "php", "uc_roles" ],
      "ON" : { "uc_roles_notify_grant" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "expiration:rid" ], "value" : "8" } },
        { "user_has_role" : {
            "account" : [ "order:customer" ],
            "roles" : { "value" : { "13" : "13" } }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "  $curtime = time();\\r\\n  $old_timestamp = $curtime;\\r\\n  $old_expirations = db_query(\\u0022SELECT expiration FROM {uc_roles_expirations} WHERE uid = %d AND rid = 13\\u0022, $order-\\u003Euid);\\r\\n  while ($old_expiration = db_fetch_object($old_expirations))\\r\\n  {\\r\\n    \\/\\/ there should really only be one entry, but for the benefit of the doubt,\\r\\n    \\/\\/ use the one with the greatest timestamp\\r\\n    if ($old_expiration-\\u003Eexpiration \\u003E $old_timestamp) {\\r\\n      $old_timestamp = $old_expiration-\\u003Eexpiration;\\r\\n    }\\r\\n  }\\r\\n\\r\\n  \\/\\/ determine how much time was left on the old role\\r\\n  $time_left = $old_timestamp - $curtime;\\r\\n  \\/\\/ add it to the new role\\r\\n  $new_timestamp = $expiration-\\u003Eexpiration + $time_left;\\r\\n  \\/\\/ write it to the expiration object and save to the DB.\\r\\n  $expiration-\\u003Eexpiration = $new_timestamp;\\r\\n  db_query(\\u0022UPDATE {uc_roles_expirations} SET expiration = %d WHERE uid = %d and rid = %d\\u0022, $new_timestamp, $order-\\u003Euid, $expiration-\\u003Erid);\\r\\n\\r\\n  \\/\\/ Delete the old expiration table entry without going through revoke (don\\u0027t want to trigger rules for it.)\\r\\n  $user = user_load($order-\\u003Euid);\\r\\n  uc_roles_delete($user, 13, TRUE);\\r\\n" } },
        { "user_remove_role" : {
            "account" : [ "order:customer" ],
            "roles" : { "value" : { "13" : "13" } }
          }
        }
      ]
    }
  }');
  $items['rules_transfer_full_membership_to_bda_req_role'] = entity_import('rules_config', '{ "rules_transfer_full_membership_to_bda_req_role" : {
      "LABEL" : "Transfer full membership to BDA req role",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "user_roles" ],
      "REQUIRES" : [ "rules", "php", "uc_roles" ],
      "ON" : { "uc_roles_notify_grant" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "expiration:rid" ], "value" : "13" } },
        { "user_has_role" : {
            "account" : [ "order:customer" ],
            "roles" : { "value" : { "8" : "8" } }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "  $curtime = time();\\r\\n  $old_timestamp = $curtime;\\r\\n  $old_expirations = db_query(\\u0022SELECT expiration FROM {uc_roles_expirations} WHERE uid = %d AND rid = 8\\u0022, $order-\\u003Euid);\\r\\n  while ($old_expiration = db_fetch_object($old_expirations))\\r\\n  {\\r\\n    \\/\\/ there should really only be one entry, but for the benefit of the doubt,\\r\\n    \\/\\/ use the one with the greatest timestamp\\r\\n    if ($old_expiration-\\u003Eexpiration \\u003E $old_timestamp) {\\r\\n      $old_timestamp = $old_expiration-\\u003Eexpiration;\\r\\n    }\\r\\n  }\\r\\n\\r\\n  \\/\\/ determine how much time was left on the old role\\r\\n  $time_left = $old_timestamp - $curtime;\\r\\n  \\/\\/ add it to the new role\\r\\n  $new_timestamp = $expiration-\\u003Eexpiration + $time_left;\\r\\n  \\/\\/ write it to the expiration object and save to the DB.\\r\\n  $expiration-\\u003Eexpiration = $new_timestamp;\\r\\n  db_query(\\u0022UPDATE {uc_roles_expirations} SET expiration = %d WHERE uid = %d and rid = %d\\u0022, $new_timestamp, $order-\\u003Euid, $expiration-\\u003Erid);\\r\\n\\r\\n  \\/\\/ Delete the old expiration table entry without going through revoke (don\\u0027t want to trigger rules for it.)\\r\\n  $user = user_load($order-\\u003Euid);\\r\\n  uc_roles_delete($user, 8, TRUE);\\r\\n" } },
        { "user_remove_role" : {
            "account" : [ "order:customer" ],
            "roles" : { "value" : { "8" : "8" } }
          }
        }
      ]
    }
  }');
  $items['uc_roles_custom_notify_when_role_renewed'] = entity_import('rules_config', '{ "uc_roles_custom_notify_when_role_renewed" : {
      "LABEL" : "Custom notify when role renewed",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "notifications" ],
      "REQUIRES" : [ "rules", "php", "uc_roles" ],
      "ON" : { "uc_roles_notify_renew" : [] },
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "uc_roles_expiration", "value" : [ "expiration" ] },
            "PROVIDE" : { "variable_added" : { "expiration_var" : "expiration variable" } }
          }
        },
        { "variable_add" : {
            "USING" : { "type" : "uc_order", "value" : [ "order" ] },
            "PROVIDE" : { "variable_added" : { "order_var" : "Order variable" } }
          }
        },
        { "uc_roles_order_email" : {
            "order" : [ "order" ],
            "expiration" : [ "expiration" ],
            "from" : "Boondockers Welcome \\u003Cadmin@boondockerswelcome.com\\u003E",
            "addresses" : "[order:email]",
            "subject" : "Your membership at [store:name] has been renewed",
            "message" : "\\u003Cp\\u003EDear [order:customer:name],\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EYour membership at [store:name] has been successfully renewed. It is now set to expire on \\u003C?php $expiration = db_query(\\u0027SELECT expiration FROM {uc_roles_expirations} WHERE uid = :uid\\u0027, array(\\u0027:uid\\u0027 =\\u003E $order_var-\\u003Euid))-\\u003EfetchField(); echo format_date($expiration, \\u0027custom\\u0027, \\u0027l, F jS, Y\\u0027);?\\u003E.\\r\\n\\r\\n\\u003C?php\\r\\n  if ($expiration_var-\\u003Erid == 13)\\r\\n  {\\r\\n    $order_user = user_load($order_var-\\u003Euid);\\r\\n    if (!in_array(\\u0027full member\\u0027, $order_user-\\u003Eroles)): ?\\u003E\\r\\n\\u003Cp\\u003EPlease note that your discounted membership level requires that you provide a boonodocking location before your membership will be fully activated. Please create a boondocking location as soon as possible to fully activate your membership.\\u003C?php endif;\\r\\n}?\\u003E\\r\\n\\r\\n\\u003Cp\\u003EThanks again,\\r\\n\\r\\n\\u003Cp\\u003EThe [store:link] team\\r\\n\\u003Cbr\\u003E[site:slogan]\\r\\n",
            "format" : "3"
          }
        }
      ]
    }
  }');
  $items['uc_roles_custom_notify_when_role_renewed_after_expiry'] = entity_import('rules_config', '{ "uc_roles_custom_notify_when_role_renewed_after_expiry" : {
      "LABEL" : "Custom notify when role renewed after expiry",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "notifications" ],
      "REQUIRES" : [ "php", "rules", "uc_roles" ],
      "ON" : { "uc_roles_notify_grant" : [] },
      "IF" : [
        { "php_eval" : { "code" : "global $user;\\r\\nreturn ($user-\\u003Euid != 0);" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "uc_roles_expiration", "value" : [ "expiration" ] },
            "PROVIDE" : { "variable_added" : { "expiration_var" : "expiration variable" } }
          }
        },
        { "variable_add" : {
            "USING" : { "type" : "uc_order", "value" : [ "order" ] },
            "PROVIDE" : { "variable_added" : { "order_var" : "Order variable" } }
          }
        },
        { "uc_roles_order_email" : {
            "order" : [ "order" ],
            "expiration" : [ "expiration" ],
            "from" : "Boondockers Welcome \\u003Cadmin@boondockerswelcome.com\\u003E",
            "addresses" : "[order:email]",
            "subject" : "Your membership at [store:name] has been renewed",
            "message" : "\\u003Cp\\u003EDear [order:customer:name],\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EYour membership at [store:name] has been successfully renewed. It is now set to expire on \\u003C?php $expiration = db_query(\\u0027SELECT expiration FROM {uc_roles_expirations} WHERE uid = :uid\\u0027, array(\\u0027:uid\\u0027 =\\u003E $order_var-\\u003Euid))-\\u003EfetchField(); echo format_date($expiration, \\u0027custom\\u0027, \\u0027l, F jS, Y\\u0027);?\\u003E.\\r\\n\\r\\n\\u003C?php\\r\\n  if ($expiration_var-\\u003Erid == 13)\\r\\n  {\\r\\n    $order_user = user_load($order_var-\\u003Euid);\\r\\n    if (!in_array(\\u0027full member\\u0027, $order_user-\\u003Eroles)): ?\\u003E\\r\\n\\u003Cp\\u003EPlease note that your discounted membership level requires that you provide a boonodocking location before your membership will be fully activated. Please create a boondocking location as soon as possible to fully activate your membership.\\u003C?php endif;\\r\\n}?\\u003E\\r\\n\\r\\n\\u003Cp\\u003EThanks again,\\r\\n\\r\\n\\u003Cp\\u003EThe [store:link] team\\r\\n\\u003Cbr\\u003E[site:slogan]\\r\\n",
            "format" : "3"
          }
        }
      ]
    }
  }');
  $items['uc_roles_custom_role_notify_grant'] = entity_import('rules_config', '{ "uc_roles_custom_role_notify_grant" : {
      "LABEL" : "Custom notify on role granted",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "notifications" ],
      "REQUIRES" : [ "php", "rules", "uc_roles" ],
      "ON" : { "uc_roles_notify_grant" : [] },
      "IF" : [
        { "php_eval" : { "code" : "global $user;\\r\\nreturn ($user-\\u003Euid == 0);" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "uc_roles_expiration", "value" : [ "expiration" ] },
            "PROVIDE" : { "variable_added" : { "expiration_var" : "Expiration Var" } }
          }
        },
        { "variable_add" : {
            "USING" : { "type" : "uc_order", "value" : [ "order" ] },
            "PROVIDE" : { "variable_added" : { "order_var" : "Order Var" } }
          }
        },
        { "uc_roles_order_email" : {
            "order" : [ "order" ],
            "expiration" : [ "expiration" ],
            "from" : "Boondockers Welcome \\u003Cadmin@boondockerswelcome.com\\u003E",
            "addresses" : "[order:email]",
            "subject" : "Your membership at [store:name] has been granted",
            "message" : "\\u003Cp\\u003EDear [order:customer:name],\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EYour membership at [store:name] has been successfully created. It is set to expire on \\u003C?php $expiration = db_query(\\u0027SELECT expiration FROM {uc_roles_expirations} WHERE uid = :uid\\u0027, array(\\u0027:uid\\u0027 =\\u003E $order_var-\\u003Euid))-\\u003EfetchField(); echo format_date($expiration, \\u0027custom\\u0027, \\u0027l, F jS, Y\\u0027);?\\u003E.\\r\\n\\u003Cp\\u003EYour login details and temporary password will arrive shortly in a separate email.\\r\\n\\r\\n\\u003C?php\\r\\n  if ($expiration_var-\\u003Erid == 13)\\r\\n  {\\r\\n    $order_user = user_load($order_var-\\u003Euid);\\r\\n    if (!in_array(\\u0027full member\\u0027, $order_user-\\u003Eroles)): ?\\u003E\\r\\n\\u003Cp\\u003EPlease note that your discounted membership level requires that you provide a boonodocking location before your membership will be fully activated. Please log in and create a boondocking location as soon as possible to fully activate your membership.\\u003C?php endif;\\r\\n}?\\u003E\\r\\n\\r\\n\\u003Cp\\u003EThanks again,\\r\\n\\r\\n\\u003Cp\\u003EThe [store:link] team\\r\\n\\u003Cbr\\u003E[site:slogan]\\r\\n",
            "format" : "3"
          }
        }
      ]
    }
  }');
  $items['uc_roles_uc_roles_custom_role_notify_reminder'] = entity_import('rules_config', '{ "uc_roles_uc_roles_custom_role_notify_reminder" : {
      "LABEL" : "Custom notify customer when a role is about to expire",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "notifications" ],
      "REQUIRES" : [ "rules", "php", "uc_roles" ],
      "ON" : { "uc_roles_notify_reminder" : [] },
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "uc_roles_expiration", "value" : [ "expiration" ] },
            "PROVIDE" : { "variable_added" : { "expiration_var" : "Expiration variable" } }
          }
        },
        { "variable_add" : {
            "USING" : { "type" : "user", "value" : [ "account" ] },
            "PROVIDE" : { "variable_added" : { "account_var" : "Account variable" } }
          }
        },
        { "uc_roles_user_email" : {
            "account" : [ "account" ],
            "expiration" : [ "expiration" ],
            "from" : "Boondockers Welcome \\u003Cadmin@boondockerswelcome.com\\u003E",
            "addresses" : "[account:mail]",
            "subject" : "Your membership at [store:name] will expire soon",
            "message" : "\\u003Cp\\u003EHi [account:name],\\u003C\\/p\\u003E\\r\\n\\r\\n\\u003Cp\\u003EThis message is to remind you that your \\u003C?php if (in_array(\\u0027founding member\\u0027, $account-\\u003Eroles) \\u0026\\u0026 !in_array(\\u0027paid member\\u0027,$account-\\u003Eroles)) echo \\u0027two years of free\\u0027; ?\\u003E membership with \\u003Ca href=\\u0027http:\\/\\/www.boondockerswelcome.com\\u0027\\u003EBoondockers Welcome\\u003C\\/a\\u003E will expire on \\u003C?php $expiration = db_query(\\u0027SELECT expiration FROM {uc_roles_expirations} WHERE uid = :uid\\u0027, array(\\u0027:uid\\u0027 =\\u003E $account-\\u003Euid))-\\u003EfetchField(); echo format_date($expiration, \\u0027custom\\u0027, \\u0027l, F jS, Y\\u0027); ?\\u003E. Once your membership expires, you will no longer be able to send or receive messages, access your bookmarks or post user recommendations.\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EPlease log in and visit \\u003Ca href=\\u0027http:\\/\\/www.boondockerswelcome.com\\/membership-products\\u0027\\u003Eour membership products page\\u003C\\/a\\u003E to renew this membership before it expires.\\u003C\\/p\\u003E\\r\\n\\r\\n\\u003Cp\\u003EThanks again,\\u003C\\/p\\u003E\\r\\n\\r\\n\\u003Cp\\u003E[store:name]\\r\\n\\u003Cbr\\u003E[site:slogan]\\u003C\\/p\\u003E",
            "format" : "3"
          }
        }
      ]
    }
  }');
  return $items;
}
