<?php
/**
 * @file
 * bdw_role_rules_feature.features.inc
 */

/**
 * Implements hook_flag_default_flags().
 */
function bdw_role_rules_feature_flag_default_flags() {
  $flags = array();
  // Exported flag: "Bookmarked Users".
  $flags['bookmarked_users'] = array(
    'entity_type' => 'user',
    'title' => 'Bookmarked Users',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Add [user:name] to your bookmarks',
    'flag_long' => 'Bookmark this member',
    'flag_message' => '[user:name] has been added to your <a href="/my_bookmarked_users">bookmarks</a>.',
    'unflag_short' => 'Remove [user:name] from your bookmarks',
    'unflag_long' => 'Unbookmark this user',
    'unflag_message' => '[user:name] has been removed from your <a href="/my_bookmarked_users">bookmarks</a>.',
    'unflag_denied_text' => '',
    'link_type' => 'normal',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 0,
      'diff_standard' => 0,
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => FALSE,
    'show_on_profile' => 0,
    'access_uid' => '',
    'module' => 'bdw_role_rules_feature',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  // Exported flag: "Bookmarks".
  $flags['bookmarks'] = array(
    'entity_type' => 'node',
    'title' => 'Bookmarks',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Bookmark this user',
    'flag_long' => 'Add this user to your bookmarks',
    'flag_message' => 'This user has been added to your bookmarks',
    'unflag_short' => 'Unbookmark this user',
    'unflag_long' => 'Remove this user from your bookmarks',
    'unflag_message' => 'This user has been removed from your bookmarks',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'teaser' => TRUE,
      'full' => TRUE,
    ),
    'show_as_field' => FALSE,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => FALSE,
    'i18n' => 0,
    'module' => 'bdw_role_rules_feature',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  // Exported flag: "User provides boondocking".
  $flags['boondocking_available'] = array(
    'entity_type' => 'user',
    'title' => 'User provides boondocking',
    'global' => 1,
    'types' => array(),
    'flag_short' => 'User provides boondocking',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'User does not provide boondocking',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(),
    'show_as_field' => FALSE,
    'show_on_form' => FALSE,
    'access_author' => '',
    'show_contextual_link' => FALSE,
    'show_on_profile' => 0,
    'access_uid' => '',
    'module' => 'bdw_role_rules_feature',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  // Exported flag: "Membership Expiring".
  $flags['membership_expiring'] = array(
    'entity_type' => 'user',
    'title' => 'Membership Expiring',
    'global' => 1,
    'types' => array(),
    'flag_short' => 'Mark as Memberhsip Expiring',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Mark as Membership Not Expiring',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 0,
      'diff_standard' => 0,
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => FALSE,
    'show_on_profile' => 0,
    'access_uid' => '',
    'module' => 'bdw_role_rules_feature',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  // Exported flag: "Purchased Membership".
  $flags['purchased_membership'] = array(
    'entity_type' => 'user',
    'title' => 'Purchased Membership',
    'global' => 1,
    'types' => array(),
    'flag_short' => 'Mark as Purchased',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Mark as Not Purchased',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(),
    'show_as_field' => FALSE,
    'show_on_form' => FALSE,
    'access_author' => '',
    'show_contextual_link' => FALSE,
    'show_on_profile' => FALSE,
    'access_uid' => '',
    'module' => 'bdw_role_rules_feature',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  return $flags;

}
