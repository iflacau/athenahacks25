import requests
from bs4 import BeautifulSoup
import json
import re
import sys

if __name__ == "__main__":
    try:
        # 1. Read the URL from standard input
        url_string = sys.stdin.readline().strip()
        if not url_string:
            raise ValueError("No URL provided via standard input.")

        #print(f"Fetching data from URL: {url_string}")

        # 2. Fetch the webpage content
        response = requests.get(url_string)
        response.raise_for_status()  # Raise HTTPError for bad responses
        soup = BeautifulSoup(response.content, 'html.parser')

        # 3. Find the script containing JSON data
        script = soup.find('script', text=re.compile('createFullCalendar'))

        if script:
            # 4. Extract JSON data using regex
            json_data = re.search(r'createFullCalendar\(\$.parseJSON\((.*?)\)\)', script.text, re.DOTALL).group(1)[1:-1]
            calendar_data = json.loads(json_data)

            # 5. Save to JSON file
            filename = 'calendar_data.json' # Fixed filename
            with open(filename, 'w') as f:
                json.dump(calendar_data, f, indent=4)
            #print(f"Data saved to '{filename}'")

        else:
            print("No relevant script found on the page.")

    except requests.exceptions.RequestException as e:
        print(f"HTTP Request Error: {e}")
    except json.JSONDecodeError as e:
        print(f"JSON Decode Error: {e}")
    except ValueError as e:
        print(f"Value Error: {e}")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")