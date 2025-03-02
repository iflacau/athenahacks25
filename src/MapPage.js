import React, { useState }  from 'react';
import './MapPage.css';
import styled, { keyframes } from 'styled-components';

const slideIn = keyframes`
  from {
    transform: translateX(100%);
  }
  to {
    transform: translateX(0);
  }
`;

const SlideContainer = styled.div`
  position: fixed;
  top: 0;
  right: 0;
  width: 50vw;
  height: 100vh;
  background-color: #292967;
  box-shadow: -20px 0 10px rgba(0, 0, 0, 0.2);
  animation: ${slideIn} 0.5s ease-out;
  display: ${({ isOpen }) => (isOpen ? 'flex' : 'none')};
  flex-direction: column;
  align-items: center;
  padding: 20px;
  z-index: 1000;
`;

const CloseButton = styled.button`
  position: absolute;
  top: 10px;
  right: 15px;
  background-color: #292967;
  color: white;
  border: none;
  padding: 8px 12px;
  border-radius: 5px;
  cursor: pointer;
`;



const buildings = [
    { name: "ENGR IV", top: "17%", left: "33%" },
    { name: "ENGR VI", top: "14%", left: "37%" },
    { name: "ENGR V", top: "20%", left: "37%" },
    { name: "BOELTER", top: "27%", left: "33%" },
    { name: "MS", top: "31%", left: "37%" },
    { name: "MOORE", top: "31%", left: "42%" },
    { name: "LAKRETZ", top: "31%", left: "25%" },
    { name: "LS", top: "39%", left: "23.25%" },
    { name: "BOYER", top: "40%", left: "29%" },
    { name: "WGYOUNG", top: "43%", left: "31%" },
    { name: "GEOLOGY", top: "44%", left: "34.75%" },
    { name: "FRANZ", top: "45%", left: "37.5%" },
    { name: "PRITZKER", top: "55%", left: "37.5%" },
    { name: "SLICHTR", top: "54%", left: "35%" },
    { name: "MOL SCI", top: "54%", left: "29.5%" },
    { name: "BIO SCI", top: "50%", left: "24%" },
    { name: "HERSHEY", top: "61%", left: "21%" },
    { name: "BOTANY", top: "54%", left: "20.5%" },
    { name: "PORTOLA", top: "44%", left: "40.5%" },
    { name: "PAB", top: "46%", left: "43.5%" },
    { name: "KNUDSEN", top: "53%", left: "43.5%" },
    { name: "KAPLAN", top: "52%", left: "48%" },
    { name: "OSTIN", top: "56%", left: "43%" },
    { name: "SMB", top: "61%", left: "44%" },
    { name: "SMB", top: "61%", left: "44%" },
    { name: "MURPHY", top: "74%", left: "48.5%" },
    { name: "HAINES", top: "52%", left: "57%" },
    { name: "ROYCE", top: "40%", left: "56%" },
    { name: "FOWLER", top: "30%", left: "56%" },
    { name: "KAUFMAN", top: "19%", left: "56%" },
    { name: "CAMPBELL", top: "51%", left: "62%" },
    { name: "PERLOFF", top: "65%", left: "59%" },
    { name: "BUNCHE", top: "65%", left: "64%" },
    { name: "PUB AFF", top: "74%", left: "63%" },
    { name: "DODD", top: "74%", left: "56%" },
    { name: "MELNITZ", top: "68%", left: "77%" },
    { name: "MACGOWN", top: "69%", left: "73%" },
    { name: "BROAD", top: "55%", left: "75%" },
    { name: "ROLFE", top: "42%", left: "62%" },
    { name: "ANDERSON", top: "32%", left: "63%" },
    { name: "CORNELL", top: "24%", left: "63%" },
    { name: "ROSNFLD", top: "25%", left: "65.5%" },
    { name: "ENTRPR", top: "26%", left: "60%" },
    { name: "GOLD", top: "20%", left: "60%" },
    { name: "COLLINS", top: "10%", left: "60%" },
  ];


function MapPage() {
    const [isPanelOpen, setIsPanelOpen] = useState(false);
    const [selectedBuilding, setSelectedBuilding] = useState(null);

    const handleClick = (building) => {
        setSelectedBuilding(building);
        setIsPanelOpen(true);
      };

    return (
      <div className="map-container">
        <img src="/img/mapofucla.png" alt="Campus Map" className="map-image" ></img>



      {buildings.map((building, index) => (
        <button
          key={index}
          className="map-button"
          style={{ top: building.top, left: building.left }}
          onClick={() => handleClick(building)}
        />
      ))}

    {/* Sliding Panel */}
    <SlideContainer isOpen={isPanelOpen}>
  <CloseButton onClick={() => setIsPanelOpen(false)}>Close</CloseButton>
  {selectedBuilding && (
    <div style={{ width: '100%', height: '80vh', overflow: 'auto' }}>
      <h2>{selectedBuilding.name}</h2>
      <p>Details about {selectedBuilding.name} can go here.</p>
    </div>
  )}
</SlideContainer>
    </div>
  );
}

export default MapPage;