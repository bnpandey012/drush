<?php

use \Drupal\node\Entity\Node;

/**
 * Implements hook_drush_command().
 */
function custom_drush_test_drush_command() {
  $items = array();
  $items['first-test'] = [
    'description' => 'This is my fist drush test',
    'aliases' => ['fst'],
  ];
  return $items;
}

/**
 * Call back function drush_custom_drush_command_say_hello()
 * The call back function name in the  following format
 *  drush_{module_name}_{item_id_for_command}()
 */
function drush_custom_drush_test_first_test() {
  $name = drush_prompt("Enter the file name", '', TRUE);
  if ($name) {
    $file_path = DRUPAL_ROOT . '/modules/custom/custom_drush_test/csv/' . $name;
    if (file_exists($file_path)) {
      if (($handle = fopen($file_path, "r")) !== FALSE) {
        $i = 0;
        while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
          $node = Node::create([
                'type' => 'drush_test',
                'title' => $data[0],
                'body' => '<span>' . $data[1] . '</span>',
                'uid' => 1
          ]);
          $node->save();
          $i++;
        }
        drush_print("$i node created!!!");
        fclose($handle);
      }
    }
    else {
      drush_print('File not exists!!');
    }
  }
  else {
    drush_print('Please enter file name');
  }
}
