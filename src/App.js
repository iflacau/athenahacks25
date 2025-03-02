
import './App.css';

import * as React from 'react';
import {useState } from 'react';
import { DemoContainer } from '@mui/x-date-pickers/internals/demo';
import { AdapterDayjs } from '@mui/x-date-pickers/AdapterDayjs';
import { LocalizationProvider } from '@mui/x-date-pickers/LocalizationProvider';
import { DatePicker } from '@mui/x-date-pickers/DatePicker';
import styled from 'styled-components';
import { Box, Typography } from '@mui/material';
import { TimePicker } from '@mui/x-date-pickers/TimePicker';
import { BrowserRouter,Routes,Route} from 'react-router-dom';
import { useNavigate } from 'react-router-dom';
import MapPage from './MapPage.js';
import dayjs from 'dayjs';

const Button = styled.button`
  background-color: #292967;
  color: white;
  padding: 10px;
  border-radius: 5px;
  border-color:rgb(69, 69, 180);
  cursor: pointer;
  margin-top: 50px;
  margin-bottom: 50px;
  font-family: 'Roboto Mono', monospace;
`;

function Home() {
  const navigate = useNavigate();

  const [selectedDate, setSelectedDate] = useState(null);
  const [startTime, setStartTime] = useState(null);
  const [endTime, setEndTime] = useState(null);
  const [error, setError] = useState(false);
  const [timeError, setTimeError] = useState(false);

  const handleSearch = () => {
    setTimeError(false); // Reset time error
    if (!selectedDate || !startTime || !endTime) {
      setError(true);
      return; // Stop execution if fields are missing
    } else {
      setError(false);
    }

    if (dayjs(startTime).isAfter(dayjs(endTime))) {
      setTimeError(true);
      return; // Stop execution if start time is after end time
    }

    navigate('/mappage', { state: { selectedDate, startTime, endTime } });
  };



  return (

    <div className="App">
      <img src = "/img/pawspotlogo.png" className = "mainimage"></img>
       <h1 className="text">Need to Lock In, Bruin?<br />Let's Find You A Room.</h1>


       <Box sx={{ display: 'flex', justifyContent: 'space-evenly', alignItems: 'center', gap: 4, width: '100%', flexWrap: 'wrap' }}>
  
  {/* Date Picker (kept separate) */}
  <Box sx={{ display: 'flex', flexDirection: 'column', alignItems: 'center' }}>
    <Typography sx={{ color: 'white', marginBottom: 1, fontFamily: 'Roboto Mono' }}>Enter the Date</Typography>
    <LocalizationProvider dateAdapter={AdapterDayjs}>
      <DemoContainer components={['DatePicker']}>
        <DatePicker 
           value={selectedDate}
          onChange={(newDate) => setSelectedDate(newDate)}
          sx={{
            backgroundColor: 'black',
            borderRadius: '5px',
            input: { color: 'white' },
            svg: { color: 'white' },
            '& .MuiInputBase-input': { fontFamily: 'Roboto Mono', fontSize: '16px', color: 'white' }
          }} 
        />
      </DemoContainer>
    </LocalizationProvider>
  </Box>

  {/* Grouped Start & End Time Pickers */}
  <Box sx={{ display: 'flex', flexDirection: 'row', gap: 2, alignItems: 'center' }}>
    {/* Start Time Picker */}
    <Box sx={{ display: 'flex', flexDirection: 'column', alignItems: 'center' }}>
      <Typography sx={{ color: 'white', marginBottom: 1, fontFamily: 'Roboto Mono' }}>Start Time</Typography>
      <LocalizationProvider dateAdapter={AdapterDayjs}>
        <DemoContainer components={['TimePicker']}>
          <TimePicker 
            value={startTime}
            onChange={(newTime) => setStartTime(newTime)}
            sx={{
              backgroundColor: 'black',
              borderRadius: '5px',
              input: { color: 'white' },
              svg: { color: 'white' },
              '& .MuiInputBase-input': { fontFamily: 'Roboto Mono', fontSize: '16px', color: 'white' }
            }} 
          />      
        </DemoContainer>
      </LocalizationProvider>
    </Box>

    {/* End Time Picker */}
    <Box sx={{ display: 'flex', flexDirection: 'column', alignItems: 'center' }}>
      <Typography sx={{ color: 'white', marginBottom: 1, fontFamily: 'Roboto Mono' }}>End Time</Typography>
      <LocalizationProvider dateAdapter={AdapterDayjs}>
        <DemoContainer components={['TimePicker']}>
          <TimePicker 
              value={endTime}
              onChange={(newTime) => setEndTime(newTime)}
            sx={{
              backgroundColor: 'black',
              borderRadius: '5px',
              input: { color: 'white' },
              svg: { color: 'white' },
              '& .MuiInputBase-input': { fontFamily: 'Roboto Mono', fontSize: '16px', color: 'white' }
            }} 
          />      
        </DemoContainer>
      </LocalizationProvider>
    </Box>
  </Box>

</Box>

{/* Fill Error Message */}
 {error && (
  <Typography sx={{ color: 'red', fontFamily: 'Roboto Mono', marginTop: 2 }}>
         Please fill in all fields before searching.
        </Typography>
    )}

{/* Time Error Message */}
  {timeError && (
    <Typography sx={{ color: 'red', fontFamily: 'Roboto Mono', marginTop: 2 }}>
        Start time must be before end time.
        </Typography>
  )}

{/* Navigate to Map Page */}
<Button onClick={handleSearch}>Search for a Room</Button>
    </div>
  );
}

function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<Home />} />
        <Route path="/mappage" element={<MapPage />} />
      </Routes>
    </BrowserRouter>
  );
}

export default App;
