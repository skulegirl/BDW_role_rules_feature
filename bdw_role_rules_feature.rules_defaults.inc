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
  $items['rules_remove_expiring_membership_flag_from_user'] = entity_import('rules_config', '{ "rules_remove_expiring_membership_flag_from_user" : {
      "LABEL" : "Remove \\u0022membership_expiring\\u0022 flag from user",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "bdw_role_rules", "flag_user" ],
      "REQUIRES" : [ "rules", "flag", "uc_roles" ],
      "ON" : { "uc_roles_notify_revoke" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "expiration:rid" ], "value" : "8" } },
        { "data_is" : { "data" : [ "expiration:rid" ], "value" : "13" } },
        { "OR" : [] }
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
      "REQUIRES" : [ "rules", "uc_roles" ],
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
      "REQUIRES" : [ "rules", "uc_roles" ],
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
