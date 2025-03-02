import requests
from bs4 import BeautifulSoup
import json
import re
import sys

if __name__ == "__main__":
    try:
        # 1. Read the URL from standard input
        url_string = "https://sa.ucla.edu/RO/Public/SOC/Search/ClassroomGridSearch"
        if not url_string:
            raise ValueError("No URL provided via standard input.")

        #print(f"Fetching data from URL: {url_string}")

        # 2. Fetch the webpage content
        response = requests.get(url_string)
        response.raise_for_status()  # Raise HTTPError for bad responses
        soup = BeautifulSoup(response.content, 'html.parser')
 
        #3. Find the script containing JSON data
        autocomplete_tag = soup.find('iwe-autocomplete', {'id': 'classroom_autocomplete'})

        if autocomplete_tag:
            options_attribute = autocomplete_tag.get('options')
        if options_attribute:
            try:
                # Parse the 'options' attribute value as JSON
                classroom_list = json.loads(options_attribute)
            except json.JSONDecodeError as e:
                print(f"Error decoding JSON from options attribute: {e}")
                print(f"Problematic options attribute value: {options_attribute}")
        else:
            print("Error: 'options' attribute not found in <iwe-autocomplete> tag.")
        

        transformed_list = []
        for item in classroom_list:
            if not isinstance(item, dict) or 'value' not in item:
                print("Warning: Input list contains an item without 'value' key or not a dictionary. Skipping:", item)
                continue # Skip to the next item

            value_str = item['value']
            parts = value_str.split('|') # Split by the delimiter '|'

            if len(parts) == 2:
                room_value = parts[0].strip()  # Building/Room part before '|'
                number_value = parts[1].strip() # Number part after '|'
                transformed_item = {
                    "room": room_value,
                    "number": number_value
                }
                transformed_list.append(transformed_item)
        
        # 5. Save to JSON file
        filename = 'classroom_data.json' # Fixed filename
        with open(filename, 'w') as f:
            json.dump(transformed_list, f, indent=4)
        #print(f"Data saved to '{filename}'")

    except requests.exceptions.RequestException as e:
        print(f"HTTP Request Error: {e}")
    except json.JSONDecodeError as e:
        print(f"JSON Decode Error: {e}")
    except ValueError as e:
        print(f"Value Error: {e}")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")